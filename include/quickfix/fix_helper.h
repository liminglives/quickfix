#!/usr/bin/env python2.7

from rttpy.opt_model.opt_model_const import *
from rttpy.platform.manager_holder import ManagerHolder
from rttpy.platform.observer_priority_const import *
from rttpy.util.config import Config
from rttpy.util.latency_tracer import *
from rttpy.optimizer.optimizer_helper import OptimizerHelper
from rttpy.util.csv_file import CsvReader

import datetime as dt
import numpy as np
import copy
import glob
import logging as log
import os
import pandas as pd
from scipy.optimize import fmin_cg, fmin_ncg


class LiveComdtyOptimizer(object):
    def __init__(self):
        static_data_manager = ManagerHolder().get_manager('StaticDataManager')
        self.__ordered_universe_rtid_list \
            = static_data_manager.factor_loading.ordered_universe_rtid_list
        self.__opt_model_manager = ManagerHolder().get_manager('OptModelManager')
        universe_type = Config().get_config('UniverseType')
        self.__comdty_universe = True if universe_type is not None \
                                 and universe_type == 'ComdtyUniverse' else False
        self.__secinfo_map = static_data_manager.sec_info_map
        self.__trading_comdty_rtid_list = static_data_manager.trading_comdty_rtid_list
        self.__factor_id_to_name_map = static_data_manager.comdty_subtype_name_dict
        self.__pid_target_list = None
        self.__portfolio_identifier = static_data_manager.portfolio_identifier
        combine_pf_list = self.__portfolio_identifier.combine_portfolio_list()
        self.__is_combine = True if combine_pf_list else False
        if self.__is_combine is True:
            pf_current_list = ['CurrentQty' + pf for pf in combine_pf_list]
            self.__pid_current_list = [
                (self.__portfolio_identifier.get_pid_by_code(pf), 'CurrentQty' + pf)
                for pf in self.__portfolio_identifier.combine_portfolio_list()]
            pf_target_list = ['TargetQty' + pf for pf in combine_pf_list]
            pf_mktval_list = ['MktVal' + pf for pf in combine_pf_list]
            self.__pid_target_list = [
                (self.__portfolio_identifier.get_pid_by_code(pf), 'TargetQty' + pf,
                 'MktVal' + pf)
                for pf in self.__portfolio_identifier.combine_portfolio_list()]

        self.__snapshot_summary = self.__opt_model_manager.snapshot_summary
        self.__factor_snapshot_summary = self.__opt_model_manager.factor_snapshot_summary
        self.__suspension_observer = self.__opt_model_manager.suspension_observer
        self.__dollarlimit_observer = self.__opt_model_manager.dollarlimit_observer
        self.__sharelimit_observer = self.__opt_model_manager.sharelimit_observer
        self.__advlimit_observer = self.__opt_model_manager.advlimit_observer
        self.__tplus1_observer = self.__opt_model_manager.tplus1_observer
        self.__capital_observer = self.__opt_model_manager.capital_observer
        self.__directed_trade_observer = self.__opt_model_manager.directed_trade_observer
        self.__updownlimit_observer = self.__opt_model_manager.updown_limit_observer
        self.__position_limit_observer = self.__opt_model_manager.position_limit_observer
        self.__manual_position_limit_observer = self.__opt_model_manager.manual_position_limit_observer
        self.__active_opt_model_list = self.__opt_model_manager.active_opt_model_list
        self.__forecast_consolidation = ManagerHolder().get_manager('ForecastConsolidation')
        self.__forecast_opt_model = None
        self.__factor_risk_model = None
        self.__residual_market_impact_model = None
        self.__instrument_penalty_model = None
        self.__iter = 0
        self.__maxiter = 100
        approximate_sqrt_decay = Config().get_config('OptModel.RMIApproximateSqrtDecay', int)
        self.__approximate_sqrt_decay = True if approximate_sqrt_decay is not None \
                                        and approximate_sqrt_decay == 1 else False

        self.__other_active_opt_model_list = []
        for active_opt_model in self.__active_opt_model_list:
            if active_opt_model.__class__.__name__ == 'RTForecastModel':
                self.__forecast_opt_model = active_opt_model
            elif active_opt_model.__class__.__name__ == 'RTInstrumentPenaltyModel':
                self.__instrument_penalty_model = active_opt_model
            elif active_opt_model.__class__.__name__ == 'RTResidualMarketImpactModel':
                self.__residual_market_impact_model = active_opt_model
            elif active_opt_model.__class__.__name__ == 'RTFactorRiskModel':
                self.__factor_risk_model = active_opt_model
                continue
            self.__other_active_opt_model_list.append(active_opt_model)

        self.__execution_manager = ManagerHolder().get_manager('ExecutorManager')

        self.__timer_manager = ManagerHolder().get_manager('TimerManager')
        history_manager = ManagerHolder().get_manager('HistoryManager')
        self.__position_recorder = history_manager.position_recorder
        self.__rmi_recorder = history_manager.rmi_recorder
        self.__trade_rtid_set = None

        if Config().get_config('Accounting.AccountingEnable', int) == 1:
            self.__accounting_manager = ManagerHolder().get_manager('AccountingManager')
        else:
            self.__accounting_manager = None

        self.__last_optimizer_trade_usecond = self.__timer_manager.today_am_usecond_since_trade()
        self.__recovery()

        if self.__last_optimizer_trade_usecond == self.__timer_manager.today_am_usecond_since_trade():
            print '========================='
            self.__residual_market_impact_model.init_new_day()

        self.__is_live = True if Config().job_type == 'Live' else False
        self.__iteration_num = 0
        self.__dump_headers = ['RTId', 'Uid', 'DateTime', 'MicroSecondSinceTrade','CurrentQty',
                               'IdealQty','TargetQty', 'FdeSum', 'Iteration', 'ForecastConsolidation',
                               'RMI', 'OptimizerBeginTradeUsecond', 'OptimizerEndTradeUsecond',
                               'OptimizerClosePrice', 'OptimizerMktVal','Eid',
                               'Exchange', 'ExchangeEnum', 'ExecutionQty']
        opt_model_header = [opt_model.__class__.__name__ for opt_model in self.__active_opt_model_list]
        self.__dump_headers.extend(opt_model_header)
        model_header = [model.__class__.__name__ \
                        for model in self.__forecast_opt_model.active_model_list]
        self.__dump_headers.extend(model_header)

        if self.__is_combine is True:
            self.__dump_headers.extend(pf_current_list)
            self.__dump_headers.extend(pf_target_list)
            self.__dump_headers.extend(pf_mktval_list)

        self.__factor_dump_headers = ['FactorId', 'FactorName', 'DateTime', 'MicroSecondSinceTrade',
                                      'FactorRet']
        self.__rtid_factor_dump_headers = ['RTId', 'Uid', 'DateTime', 'MarketBeta', 'IndustryBeta']
        self.__optimizer_dir = Config().get_config('Live.OptimizerDir')
        if not os.path.isdir(self.__optimizer_dir):
            os.makedirs(self.__optimizer_dir)
        self.__meta_dir = Config().get_config('Live.MetaDir')
        if not os.path.isdir(self.__meta_dir):
            os.makedirs(self.__meta_dir)
        self.__ordered_current_position_array = None
        self.__begin_time = dt.datetime.now()
        self.__delta_dollar_position_limit = Config().get_config(
            'Optimizer.DeltaDollarPositionLimit', float)

    def utility(self, x, sign=1.0):
        #print x, 'trying postions in optimizer util'
        f_sum = 0.0
        for active_opt_model in self.__active_opt_model_list:
            util = active_opt_model.utility(x, sign)
            f_sum += util
        #print f_sum, "total utility iteration"
        return f_sum

    def fde(self, x, sign=1.0):
        #print x, 'trying positions in optimizer fde'
        Df_sum = 0.0
        self.__iter += 1
        for active_opt_model in self.__active_opt_model_list:
            model_fde = active_opt_model.fde(x, sign) 
            Df_sum += model_fde
        #print Df_sum, abs(Df_sum).sum(), 'total abs Df sum', 'iteration', self.__iter
        #print Df_sum, Df_sum.shape, 'test Df sum shape'
        return np.minimum(np.maximum(self.__ordered_price_array * -0.1,
                               Df_sum), self.__ordered_price_array * 0.1)

    def D_diag_vec(self, x, sign=1.0):
        d_diag_vec = 0.0
        for active_opt_model in self.__other_active_opt_model_list:
            d_diag_vec += active_opt_model.sde_diag_vec(x, sign)
        #print H_sum, 'total H', 'iteration', self.__iter, H_sum.shape, type(H_sum)
        return d_diag_vec

    def sde_inverse(self, D_diag_vec):
        D_diag_inv = 1 / D_diag_vec
        U, Ut, C_inv = self.__factor_risk_model.U, self.__factor_risk_model.Ut, \
                       self.__factor_risk_model.C_inv
        return np.diag(D_diag_inv) - np.dot(np.dot(np.multiply(D_diag_inv[:, np.newaxis], Ut),
                                                   np.linalg.inv(C_inv + np.dot(U * D_diag_inv, Ut))),
                                            U * D_diag_inv)
                                                                     

    def calculate(self, init_position_vec):
        pre_utility = self.utility(init_position_vec)
        pre_position_vec = init_position_vec
        while self.__iteration_num < self.__maxiter:
            alpha = 1.0
            numreduce = 0
            self.__iteration_num += 1
            fde_vec = self.fde(pre_position_vec)
            D_diag_vec = self.D_diag_vec(pre_position_vec)
            sde_m = self.sde_inverse(D_diag_vec)
            delta_position = np.dot(fde_vec, sde_m)
            position_vec = pre_position_vec - alpha * delta_position
            utility = self.utility(position_vec)
            if (abs(utility - pre_utility) < 1e-6 * abs(pre_utility)) \
                and ((self.fde(position_vec)**2).sum() < 1e-6 * pre_utility**2) \
                and ((position_vec - pre_position_vec)**2).sum() < 5e-5 * (pre_position_vec**2).sum():
                return position_vec
            while utility - pre_utility > 0:
                numreduce += 1
                if numreduce >= 20:
                    print " no way to reduce utility at. Optimizer stopped for the cycle", pre_position_vec
                    return pre_position_vec 
                alpha *= 0.5
                #print " position overshoot, reducing alpha to " + str(alpha)
                position_vec = pre_position_vec - alpha * delta_position
                utility = self.utility(position_vec)
            pre_position_vec = position_vec
            pre_utility = utility
        print 'Maximum number of iterations reached. Optimizer stopped for this cycle'
        return position_vec

    @latency
    def optimize(self):
        res = self.calculate(self.__ordered_current_position_array)

        end_time = dt.datetime.now()
        print 'time cost for this optimize is', end_time - self.__begin_time
        self.__begin_time = end_time
        print 'gggggggggggggggggggg'
        #print 'target position', res
        #print 'forecast ', self.__forecast_opt_model.forecast_consolidation_forecast_vec
        self.__iter = 0
        return res

    def __round_target_position(self, rtid_vec, ideal_position_vec):
        if self.__comdty_universe is False:
            position_vec = np.array(ideal_position_vec)
            for i in xrange(len(ideal_position_vec)):
                if -const.kFillSizeDivisor < ideal_position_vec[i] < const.kFillSizeDivisor:
                    position_vec[i] = 0.0
            round_target_position_vec = np.round(position_vec / const.kFillSizeDivisor) *\
                                        const.kFillSizeDivisor
        else:
            position_vec = np.array(ideal_position_vec)
            for i in xrange(len(ideal_position_vec)):
                rtid = rtid_vec[i]
                trading_unit = self.__secinfo_map[rtid].trading_unit
                if -trading_unit < ideal_position_vec[i] < trading_unit:
                    position_vec[i] = 0.0
                else:
                    position_vec[i] = np.round(position_vec[i] / trading_unit) * trading_unit
            round_target_position_vec = np.array(position_vec)
        return round_target_position_vec

    @latency
    def __pre_calculate(self):
        for active_opt_model in self.__active_opt_model_list:
            active_opt_model.pre_calculate()

    def __limit_target_position(self, current_position_vec, position_vec):
        upper_limit_vec = self.__instrument_penalty_model.target_upper_limit_vec
        lower_limit_vec = self.__instrument_penalty_model.target_lower_limit_vec
        limited_target_position_vec = position_vec.copy()
        for i in xrange(len(position_vec)):
            upper_limit_vec[i] = current_position_vec[i] \
                if current_position_vec[i] > upper_limit_vec[i] else upper_limit_vec[i]
            lower_limit_vec[i] = current_position_vec[i] \
                if current_position_vec[i] < lower_limit_vec[i] else lower_limit_vec[i]

        for i in xrange(len(position_vec)):
            limited_target_position_vec[i] = upper_limit_vec[i] \
                if position_vec[i] > upper_limit_vec[i] else lower_limit_vec[i] \
                   if position_vec[i] < lower_limit_vec[i] else position_vec[i]
        return limited_target_position_vec

    def __check_target_position(self, current_position, target_position):
        if self.__delta_dollar_position_limit is not None:
            price_array = self.__snapshot_summary.ordered_price_array
            delta_position = np.abs(target_position - current_position)
            delta_dollar_position = delta_position * price_array
            checked_target_position = np.zeros(len(current_position))
            for i in xrange(len(current_position)):
                checked_target_position[i] = target_position[i] \
                    if delta_dollar_position[i] >= self.__delta_dollar_position_limit \
                       else current_position[i]
            return checked_target_position
        return target_position

    def __recovery(self):
        checkpoint_collector = ManagerHolder().get_manager('CheckpointCollector')
        checkpoint_epoch_usecond = checkpoint_collector.checkpoint_epoch_usecond
        live_optimizer_dir = Config().get_config('Live.OptimizerDir')
        optimizer_files_pattern = live_optimizer_dir + '/optimizer.*.csv'
        optimizer_file_list = glob.glob(optimizer_files_pattern)
        time_optimizer_file_dict = {}
        for optimizer_file in optimizer_file_list:
            epoch_usecond = os.path.basename(optimizer_file).split('.')[1]
            epoch_usecond = int(epoch_usecond.strip())
            time_optimizer_file_dict[epoch_usecond] = optimizer_file

        today_am_open_epoch_usecond = self.__timer_manager.today_am_open_timestamp().usecond_since_epoch
        if self.__approximate_sqrt_decay is True and today_am_open_epoch_usecond != checkpoint_epoch_usecond:
            self.__rmi_recorder.recovery_approximate_sqrt_live_rmi(checkpoint_epoch_usecond)
            
        epoch_usecond_list = sorted(time_optimizer_file_dict.keys())
        for epoch_usecond in epoch_usecond_list:
            optimizer_file = time_optimizer_file_dict[epoch_usecond]
            if epoch_usecond <= checkpoint_epoch_usecond:
                optimizer_reader = CsvReader(optimizer_file)
                for optimizer_row in optimizer_reader.content:
                    rtid = int(optimizer_row['RTId'])
                    target_position = float(optimizer_row['TargetQty'])
                    self.__position_recorder.set_recovery_position(rtid, target_position)
                    if self.__approximate_sqrt_decay is False:
                        rmi = float(optimizer_row['RMI'])
                        self.__rmi_recorder.set_post_rmi(rtid, rmi)
                optimizer_reader.close()
                print 'load optimizer file ', optimizer_file
            else:
                print 'remove optimizer file ', optimizer_file
                os.remove(optimizer_file)
        self.__last_optimizer_trade_usecond = self.__timer_manager.epoch_usecond_to_trade_usecond(
            checkpoint_epoch_usecond)

    def update_forecast(self):
        self.__forecast_consolidation.init_new_sampling()

    def eod_update(self):
        if self.__accounting_manager is not None:
            self.__accounting_manager.eod_update()
    def resend(self):
        self.__snapshot_summary.update_summary_data()
        self.__ordered_current_position_array = np.array(self.__position_recorder.get_position_list(
            self.__snapshot_summary.ordered_trade_universe_rtid_list))
        target_position_array = self.__ordered_current_position_array.copy()
        if self.__execution_manager is not None:
            self.__execution_manager.send_optimizer_target_position(
                self.__snapshot_summary.ordered_trade_universe_rtid_list,
                self.__ordered_current_position_array,
                target_position_array)
            self.__execution_manager.clear_cached_target_position()

    def update_optimizer(self, end_epoch_usecond):
        optimizer_filename = self.__optimizer_dir + '/optimizer.' + str(end_epoch_usecond) + '.csv'
        optimizer_writer = CsvWriter(optimizer_filename, self.__dump_headers)
        optimizer_writer.write_header()

        now_trade_usecond = self.__timer_manager.epoch_usecond_to_trade_usecond(
            end_epoch_usecond)
        if self.__residual_market_impact_model is not None:
            self.__residual_market_impact_model.init_new_sampling(
                now_trade_usecond - self.__last_optimizer_trade_usecond)

        self.__snapshot_summary.update_summary_data()
        if self.__capital_observer is not None:
            self.__capital_observer.update()
        self.__suspension_observer.update_suspension_data()
        self.__advlimit_observer.update_advlimit_data()
        self.__dollarlimit_observer.update_dollarlimit_data()
        self.__sharelimit_observer.update_sharelimit_data()
        if self.__tplus1_observer is not None:
            self.__tplus1_observer.update_tplus1_data()
        if self.__directed_trade_observer is not None:
            self.__directed_trade_observer.update_directed_trade_data()
        if self.__updownlimit_observer is not None:
            self.__updownlimit_observer.update_updown_limit_data()
        if self.__position_limit_observer is not None:
            self.__position_limit_observer.update_limit_data()
        if self.__manual_position_limit_observer is not None:
            self.__manual_position_limit_observer.update_manual_pos_limit_data()

        self.__trade_rtid_set = self.__snapshot_summary.trade_universe_rtid_set
        self.__ordered_price_array = self.__snapshot_summary.ordered_price_array
             
        self.__ordered_current_position_array = np.array(self.__position_recorder.get_position_list(
            self.__snapshot_summary.ordered_trade_universe_rtid_list))

        self.__pre_calculate()

        res = self.optimize()
        fde_vec = self.fde(res)
        limited_target_position_vec = self.__limit_target_position(
            self.__ordered_current_position_array, res)
        ordered_trade_universe_rtid_list = self.__snapshot_summary.ordered_trade_universe_rtid_list

        round_target_position_vec = self.__round_target_position(
            self.__snapshot_summary.ordered_trade_universe_rtid_list,
            limited_target_position_vec)
        checked_target_position_vec = self.__check_target_position(
            self.__ordered_current_position_array, round_target_position_vec)

        target_info_summary = self.__execution_manager.send_optimizer_target_position(
                ordered_trade_universe_rtid_list, self.__ordered_current_position_array,
                checked_target_position_vec)
        executor_target_info_list = target_info_summary.target_info_list
        #self.__execution_manager.clear_cached_target_position()
        filled_target_info_dict = self.__accounting_manager.live_fill(
            end_epoch_usecond, executor_target_info_list,
            now_trade_usecond - self.__last_optimizer_trade_usecond)
        
        filled_target_position_vec = np.full(len(ordered_trade_universe_rtid_list), 0.0)
        for i in xrange(len(ordered_trade_universe_rtid_list)):
            rtid = ordered_trade_universe_rtid_list[i]
            filled_target_position = filled_target_info_dict[rtid].filled_position
            filled_target_position_vec[i] = filled_target_position

        if self.__residual_market_impact_model is not None and self.__rmi_recorder is not None:
            trade_usecond = self.__timer_manager.span_trade_usecond()
            delta_position_vec = filled_target_position_vec - self.__ordered_current_position_array
            if self.__residual_market_impact_model.sqrt_decay is True:
                for i in xrange(len(ordered_trade_universe_rtid_list)):
                    delta_position = delta_position_vec[i]
                    if delta_position == 0.0:
                        continue
                    a2 = self.__residual_market_impact_model.a2_vec[i]
                    rtid = ordered_trade_universe_rtid_list[i]
                    self.__rmi_recorder.set_realtime_rmi_components(rtid, trade_usecond, a2, delta_position)
            elif self.__residual_market_impact_model.approximate_sqrt_decay is True:
                a_vec = self.__residual_market_impact_model.a_vec
                hl_vec = self.__residual_market_impact_model.hl_vec
                for i in xrange(len(ordered_trade_universe_rtid_list)):
                    delta_position = delta_position_vec[i]
                    if delta_position == 0.0:
                        continue
                    rtid = ordered_trade_universe_rtid_list[i]
                    a2 = self.__residual_market_impact_model.a2_vec[i]
                    addend_vec = a2 * (abs(delta_position) ** 0.5) * np.sign(delta_position) \
                                 * self.__residual_market_impact_model.rmi_multiplier \
                                 * self.__residual_market_impact_model.a_vec \
                                 * np.exp(1.0 / self.__residual_market_impact_model.hl_vec)
                    self.__rmi_recorder.add_approximate_update(rtid, trade_usecond, addend_vec)
            else:
                addend_vec = self.__residual_market_impact_model.a2_vec * (abs(delta_position_vec) ** 0.5) \
                             * np.sign(delta_position_vec) * self.__residual_market_impact_model.rmi_multiplier
                self.__rmi_recorder.add_update(self.__snapshot_summary.ordered_trade_universe_rtid_list,
                                               addend_vec)

        iteration = self.__iteration_num
        self.__iteration_num = 0
        self.__position_recorder.set_position_list(filled_target_info_dict)

        short_mktval = 0.0
        long_mktval = 0.0
        abs_mktval = 0.0
        for i in xrange(len(ordered_trade_universe_rtid_list)):
            row = {}
            rtid = ordered_trade_universe_rtid_list[i]
            accounting_price = self.__snapshot_summary.accounting_price(rtid)
            mktval = filled_target_position_vec[i] * accounting_price
            row['RTId'] = rtid
            secinfo = self.__secinfo_map[rtid]
            uid = secinfo.uid
            eid = secinfo.eid
            trading_unit = secinfo.trading_unit
            exchange = secinfo.exchange
            row['Eid'] = eid
            row['Exchange'] = exchange
            row['Uid'] = uid
            exchange_enum = -1
            if exchange == 'CZC':
                exchange_enum = 5
            elif exchange == 'DCE':
                exchange_enum = 4
            elif exchange == 'SHF':
                exchange_enum = 3
            row['ExchangeEnum'] = exchange_enum
            row['Uid'] = self.__secinfo_map[rtid].uid
            row['DateTime'] = self.__timer_manager.timenow_str()
            row['MicroSecondSinceTrade'] = self.__timer_manager.now_trade_usecond()
            current_qty = self.__ordered_current_position_array[i]
            row['CurrentQty'] = current_qty
            row['IdealQty'] = res[i]
            row['FdeSum'] = fde_vec[i]
            target_position = filled_target_position_vec[i]
            row['TargetQty'] = target_position
            row['ExecutionQty'] = target_position / trading_unit
            row['Iteration'] = iteration
            row['OptimizerBeginTradeUsecond'] = self.__last_optimizer_trade_usecond
            row['OptimizerEndTradeUsecond'] = now_trade_usecond
            row['OptimizerClosePrice'] = self.__snapshot_summary.accounting_price(rtid)
            if self.__is_combine is True:
                for pid, header in self.__pid_current_list:
                    row[header] = target_info_summary.pid_current_position_dict[pid][i]
                for pid, position_header, mktval_header in self.__pid_target_list:
                    tg_position = target_info_summary.pid_target_position_dict[pid][i]
                    row[position_header] = tg_position
                    row[mktval_header] = tg_position * accounting_price

            row['OptimizerMktVal'] = mktval
            if mktval > 0.0:
                long_mktval += mktval
            else:
                short_mktval += mktval
            abs_mktval += abs(mktval)
            for active_opt_model in self.__active_opt_model_list:
                row[active_opt_model.__class__.__name__] = active_opt_model.fde_vec[i]
            row['ForecastConsolidation'] \
                = self.__forecast_opt_model.forecast_consolidation_forecast_vec[i]
            if self.__approximate_sqrt_decay is False:
                row['RMI'] = self.__rmi_recorder.post_rmi(rtid)
            else:
                row['RMI'] = 0.0
            for model, vec in self.__forecast_opt_model.active_model_forecast_vec_map.items():
                row[model.__class__.__name__] = vec[i]
            optimizer_writer.write_row(row)
            if target_position - current_qty != 0.0:
                log.critical('comdty target position change: uid ' + str(uid) + ' current ' \
                             + str(current_qty) + ' target '  + str(target_position) \
                             + ' delta ' + str(target_position - current_qty))

        optimizer_writer.flush()
        optimizer_writer.close()
        log.critical('comdty long market val: ' + str(long_mktval) + ' short market val: ' \
                     + str(short_mktval) + ' total abs market val: ' + str(abs_mktval))

        factor_filename = self.__optimizer_dir + '/factor.' + str(end_epoch_usecond) + '.csv'
        factor_writer = CsvWriter(factor_filename, self.__factor_dump_headers)
        factor_writer.write_header()
        for factor_id in self.__factor_snapshot_summary.factor_id_list:
            row = {}
            row['FactorId'] = factor_id
            row['FactorName'] = self.__factor_id_to_name_map[factor_id]
            row['DateTime'] = self.__timer_manager.timenow_str()
            row['MicroSecondSinceTrade'] = self.__timer_manager.now_trade_usecond()
            row['FactorRet'] = self.__factor_snapshot_summary.factor_ret_to_prev_date(factor_id)
            factor_writer.write_row(row)
        factor_writer.flush()
        factor_writer.close()

        rtid_factor_filename = self.__optimizer_dir + '/rtid_factor.' + str(end_epoch_usecond) + '.csv'
        rtid_factor_writer = CsvWriter(rtid_factor_filename, self.__rtid_factor_dump_headers)
        rtid_factor_writer.write_header()
        for rtid in self.__trading_comdty_rtid_list:
            row = {}
            row['RTId'] = rtid
            row['Uid'] = self.__secinfo_map[rtid].uid
            row['DateTime'] = self.__timer_manager.timenow_str()
            market_beta = self.__snapshot_summary.market_beta_map[rtid] \
                          if self.__snapshot_summary.market_beta_map.has_key(rtid) \
                             else 1.0
            row['MarketBeta'] = market_beta
            industry_beta = self.__snapshot_summary.industry_beta_map[rtid] \
                            if self.__snapshot_summary.industry_beta_map.has_key(rtid) else 1.0
            row['IndustryBeta'] = industry_beta
            rtid_factor_writer.write_row(row)
        rtid_factor_writer.flush()
        rtid_factor_writer.close()
        if self.__approximate_sqrt_decay is True:
            self.__rmi_recorder.dump_approximate_sqrt_live_rmi(end_epoch_usecond)
        temp_filename = self.__optimizer_dir + '/temp'
        temp_file = open(temp_filename, 'wb')
        temp_file.write(str(end_epoch_usecond))
        temp_file.flush()
        temp_file.close()
        done_filename = self.__meta_dir + '/optimizer.meta'
        os.rename(temp_filename, done_filename)
        self.__last_optimizer_trade_usecond = now_trade_usecond








#!/usr/bin/env python2.7

from rttpy.opt_model.opt_model_const import *
from rttpy.platform.manager_holder import ManagerHolder
from rttpy.platform.observer_priority_const import *
from rttpy.util.config import Config
from rttpy.util.latency_tracer import *
from rttpy.optimizer.optimizer_helper import OptimizerHelper
from rttpy.util.csv_file import CsvReader

import datetime as dt
import numpy as np
import copy
import glob
import logging as log
import os
import pandas as pd
from rttpy.optimizer.optimizer_func import rtfmin_ncg

class LiveComdtyOptimizer(object):
    def __init__(self):
        static_data_manager = ManagerHolder().get_manager('StaticDataManager')
        self.__ordered_universe_rtid_list \
            = static_data_manager.factor_loading.ordered_universe_rtid_list
        self.__opt_model_manager = ManagerHolder().get_manager('OptModelManager')
        universe_type = Config().get_config('UniverseType')
        self.__comdty_universe = True if universe_type is not None \
                                 and universe_type == 'ComdtyUniverse' else False
        self.__ignore_suspend = Config().get_config_enable('Optimizer.IgnoreSuspendEquity')
        self.__load_calendar_dict = Config().get_config_enable('Timer.LoadCalendarDict')
        self.__effective_rtid_list = []
        self.__effective_idx_list = []
        self.__fill_gap_rtid_list = []
        self.__fill_gap_idx_list = []
        self.__idx_pos_dict = {}

        self.__secinfo_map = static_data_manager.sec_info_map
        self.__trading_comdty_rtid_list = static_data_manager.trading_comdty_rtid_list
        self.__factor_id_to_name_map = static_data_manager.comdty_subtype_name_dict
        self.__pid_target_list = None
        self.__portfolio_identifier = static_data_manager.portfolio_identifier
        combine_pf_list = self.__portfolio_identifier.combine_portfolio_list()
        self.__is_combine = True if combine_pf_list else False
        if self.__is_combine is True:
            pf_current_list = ['CurrentQty' + pf for pf in combine_pf_list]
            self.__pid_current_list = [
                (self.__portfolio_identifier.get_pid_by_code(pf), 'CurrentQty' + pf)
                for pf in self.__portfolio_identifier.combine_portfolio_list()]
            pf_target_list = ['TargetQty' + pf for pf in combine_pf_list]
            pf_mktval_list = ['MktVal' + pf for pf in combine_pf_list]
            self.__pid_target_list = [
                (self.__portfolio_identifier.get_pid_by_code(pf), 'TargetQty' + pf,
                 'MktVal' + pf)
                for pf in self.__portfolio_identifier.combine_portfolio_list()]

        self.__snapshot_summary = self.__opt_model_manager.snapshot_summary
        self.__factor_snapshot_summary = self.__opt_model_manager.factor_snapshot_summary
        self.__suspension_observer = self.__opt_model_manager.suspension_observer
        self.__dollarlimit_observer = self.__opt_model_manager.dollarlimit_observer
        self.__sharelimit_observer = self.__opt_model_manager.sharelimit_observer
        self.__advlimit_observer = self.__opt_model_manager.advlimit_observer
        self.__tplus1_observer = self.__opt_model_manager.tplus1_observer
        self.__capital_observer = self.__opt_model_manager.capital_observer
        self.__directed_trade_observer = self.__opt_model_manager.directed_trade_observer
        self.__updownlimit_observer = self.__opt_model_manager.updown_limit_observer
        self.__position_limit_observer = self.__opt_model_manager.position_limit_observer
        self.__manual_position_limit_observer = self.__opt_model_manager.manual_position_limit_observer
        self.__active_opt_model_list = self.__opt_model_manager.active_opt_model_list
        self.__forecast_consolidation = ManagerHolder().get_manager('ForecastConsolidation')
        self.__forecast_opt_model = None
        self.__factor_risk_model = None
        self.__residual_market_impact_model = None
        self.__instrument_penalty_model = None
        self.__iter = 0
        self.__maxiter = 100
        approximate_sqrt_decay = Config().get_config('OptModel.RMIApproximateSqrtDecay', int)
        self.__approximate_sqrt_decay = True if approximate_sqrt_decay is not None \
                                        and approximate_sqrt_decay == 1 else False

        self.__other_active_opt_model_list = []
        for active_opt_model in self.__active_opt_model_list:
            if active_opt_model.__class__.__name__ == 'RTForecastModel':
                self.__forecast_opt_model = active_opt_model
            elif active_opt_model.__class__.__name__ == 'RTInstrumentPenaltyModel':
                self.__instrument_penalty_model = active_opt_model
            elif active_opt_model.__class__.__name__ == 'RTResidualMarketImpactModel':
                self.__residual_market_impact_model = active_opt_model
            elif active_opt_model.__class__.__name__ == 'RTFactorRiskModel':
                self.__factor_risk_model = active_opt_model
                continue
            self.__other_active_opt_model_list.append(active_opt_model)

        self.__execution_manager = ManagerHolder().get_manager('ExecutorManager')

        self.__timer_manager = ManagerHolder().get_manager('TimerManager')
        history_manager = ManagerHolder().get_manager('HistoryManager')
        self.__position_recorder = history_manager.position_recorder
        self.__rmi_recorder = history_manager.rmi_recorder
        self.__trade_rtid_set = None

        if Config().get_config('Accounting.AccountingEnable', int) == 1:
            self.__accounting_manager = ManagerHolder().get_manager('AccountingManager')
        else:
            self.__accounting_manager = None

        self.__last_optimizer_trade_usecond = self.__timer_manager.today_open_usecond_since_trade()
        self.__recovery()

        if self.__last_optimizer_trade_usecond == self.__timer_manager.today_open_usecond_since_trade():
            print '========================='
            self.__residual_market_impact_model.init_new_day()

        self.__is_live = True if Config().job_type == 'Live' else False
        self.__iteration_num = 0
        self.__dump_headers = ['RTId', 'Uid', 'DateTime', 'MicroSecondSinceTrade','CurrentQty',
                               'IdealQty','TargetQty', 'FdeSum', 'Iteration', 'ForecastConsolidation',
                               'RMI', 'OptimizerBeginTradeUsecond', 'OptimizerEndTradeUsecond',
                               'OptimizerClosePrice', 'OptimizerMktVal','Eid',
                               'Exchange', 'ExchangeEnum', 'ExecutionQty']
        opt_model_header = [opt_model.__class__.__name__ for opt_model in self.__active_opt_model_list]
        self.__dump_headers.extend(opt_model_header)
        model_header = [model.__class__.__name__ \
                        for model in self.__forecast_opt_model.active_model_list]
        self.__dump_headers.extend(model_header)

        if self.__is_combine is True:
            self.__dump_headers.extend(pf_current_list)
            self.__dump_headers.extend(pf_target_list)
            self.__dump_headers.extend(pf_mktval_list)

        self.__factor_dump_headers = ['FactorId', 'FactorName', 'DateTime', 'MicroSecondSinceTrade',
                                      'FactorRet']
        self.__rtid_factor_dump_headers = ['RTId', 'Uid', 'DateTime', 'MarketBeta', 'IndustryBeta']
        self.__optimizer_dir = Config().get_config('Live.OptimizerDir')
        if not os.path.isdir(self.__optimizer_dir):
            os.makedirs(self.__optimizer_dir)
        self.__meta_dir = Config().get_config('Live.MetaDir')
        if not os.path.isdir(self.__meta_dir):
            os.makedirs(self.__meta_dir)
        self.__ordered_current_position_array = None
        self.__begin_time = dt.datetime.now()
        self.__delta_dollar_position_limit = Config().get_config(
            'Optimizer.DeltaDollarPositionLimit', float)

    def utility(self, x, sign=1.0):
        if self.__ignore_suspend is True:
            opt_input_len = len(self.__snapshot_summary.ordered_trade_universe_rtid_list)
            opt_input_x = np.zeros(opt_input_len)
            m = 0
            if len(x) + len(self.__idx_pos_dict) != opt_input_len:
                log.error('Alert:( ignore suspend input x + suspend count not equal origal count ' + str(len(x)) + ' ' + str(len(self.__idx_pos_dict)) +  ' ' + str(opt_input_len))
                exit(1)
            for i in xrange(opt_input_len):
                if i in self.__idx_pos_dict:
                    opt_input_x[i] = self.__idx_pos_dict[i]
                else:
                    opt_input_x[i] = x[m]
                    m += 1
        else:
            opt_input_x = x

        f_sum = 0.0
        for active_opt_model in self.__active_opt_model_list:
            util = active_opt_model.utility(opt_input_x, sign)
            f_sum += util
        return f_sum

    def fde(self, x, sign=1.0, force_all = False):
        if self.__ignore_suspend is True and force_all is False:
            opt_input_len = len(self.__snapshot_summary.ordered_trade_universe_rtid_list)
            opt_input_x = np.zeros(opt_input_len)
            m = 0
            if len(x) + len(self.__idx_pos_dict) != opt_input_len:
                log.error('Alert:( ignore suspend input x + suspend count not equal origal count ' + str(len(x)) + ' ' + str(len(self.__idx_pos_dict)) +  ' ' + str(opt_input_len))
                exit(1)
            for i in xrange(opt_input_len):
                if i in self.__idx_pos_dict:
                    opt_input_x[i] = self.__idx_pos_dict[i]
                else:
                    opt_input_x[i] = x[m]
                    m += 1
        else:
            opt_input_x = x
        Df_sum = 0.0
        self.__iter += 1
        for active_opt_model in self.__active_opt_model_list:
            model_fde = active_opt_model.fde(opt_input_x, sign) 
            Df_sum += model_fde

        if self.__ignore_suspend is True and force_all is False:
            opt_output_vec = Df_sum[self.__effective_idx_list]
        else:
            opt_output_vec = Df_sum
        return opt_output_vec

    def D_diag_vec(self, x, sign=1.0):
        if self.__ignore_suspend is True:
            opt_input_len = len(self.__snapshot_summary.ordered_trade_universe_rtid_list)
            opt_input_x = np.zeros(opt_input_len)
            m = 0
            if len(x) + len(self.__idx_pos_dict) != opt_input_len:
                log.error('Alert:( ignore suspend input x + suspend count not equal origal count ' + str(len(x)) + ' ' + str(len(self.__idx_pos_dict)) +  ' ' + str(opt_input_len))
                exit(1)
            for i in xrange(opt_input_len):
                if i in self.__idx_pos_dict:
                    opt_input_x[i] = self.__idx_pos_dict[i]
                else:
                    opt_input_x[i] = x[m]
                    m += 1
        else:
            opt_input_x = x

        d_diag_vec = 0.0
        for active_opt_model in self.__other_active_opt_model_list:
            d_diag_vec += active_opt_model.sde_diag_vec(opt_input_x, sign)

        if self.__ignore_suspend is True:
            diag_output_vec = d_diag_vec[self.__effective_idx_list]
        else:
            diag_output_vec = d_diag_vec

        return diag_output_vec

    def sde_inverse(self, D_diag_vec):
        D_diag_inv = 1 / D_diag_vec
        U, Ut, C_inv = self.__factor_risk_model.U, self.__factor_risk_model.Ut, \
                       self.__factor_risk_model.C_inv

        if self.__ignore_suspend is True:
            output_U = np.zeros((len(D_diag_inv), len(D_diag_inv)))
            output_Ut = np.zeros((len(D_diag_inv), len(D_diag_inv)))
            output_U = U[:,self.__effective_idx_list]
            output_Ut = Ut[self.__effective_idx_list,]
        else:
            output_U = U
            output_Ut = Ut
        return np.diag(D_diag_inv) - np.dot(np.dot(np.multiply(D_diag_inv[:, np.newaxis], output_Ut),
                                                   np.linalg.inv(C_inv + np.dot(output_U * D_diag_inv, output_Ut))),
                                            output_U * D_diag_inv)

    def sde_inv(self, x, sign = 1.0):
        D_diag_vec = self.D_diag_vec(x)
        sde_inv_m = self.sde_inverse(D_diag_vec)
        return sde_inv_m

    def calculate(self, init_position_vec):
        pre_utility = self.utility(init_position_vec)
        pre_position_vec = init_position_vec
        while self.__iteration_num < self.__maxiter:
            alpha = 1.0
            numreduce = 0
            self.__iteration_num += 1
            fde_vec = self.fde(pre_position_vec)
            D_diag_vec = self.D_diag_vec(pre_position_vec)
            sde_m = self.sde_inverse(D_diag_vec)
            delta_position = np.dot(fde_vec, sde_m)
            position_vec = pre_position_vec - alpha * delta_position
            utility = self.utility(position_vec)
            if (abs(utility - pre_utility) < 1e-6 * abs(pre_utility)) \
                and ((self.fde(position_vec)**2).sum() < 1e-6 * pre_utility**2) \
                and ((position_vec - pre_position_vec)**2).sum() < 5e-5 * (pre_position_vec**2).sum():
                return position_vec
            while utility - pre_utility > 0:
                numreduce += 1
                if numreduce >= 20:
                    print " no way to reduce utility at. Optimizer stopped for the cycle", pre_position_vec
                    return pre_position_vec 
                alpha *= 0.5
                #print " position overshoot, reducing alpha to " + str(alpha)
                position_vec = pre_position_vec - alpha * delta_position
                utility = self.utility(position_vec)
            pre_position_vec = position_vec
            pre_utility = utility
        print 'Maximum number of iterations reached. Optimizer stopped for this cycle'
        return position_vec

    @latency
    def optimize(self):
        if self.__ignore_suspend is True:
            input_position_vec = self.__ordered_current_position_array[self.__effective_idx_list]
        else:
            input_position_vec = self.__ordered_current_position_array
        res = rtfmin_ncg(self.utility, input_position_vec,
                         self.fde, fhess_inv=self.sde_inv, maxiter=300, full_output=True,
                         avextol=1e-05, epsilon=1.4901161193847656e-08)
        end_time = dt.datetime.now()
        print 'time cost for this optimize is', end_time - self.__begin_time
        self.__begin_time = end_time
        self.__iter = 0
        self.__iteration_num = res[2] - 1
        result = res[0]
        if self.__ignore_suspend is True:
            origin_len = len(self.__snapshot_summary.ordered_trade_universe_rtid_list)
            output_result = np.zeros(origin_len)
            m = 0
            for i in range(origin_len):
                if i in self.__idx_pos_dict:
                    output_result[i] = self.__idx_pos_dict[i]
                else:
                    output_result[i] = result[m]
                    m += 1
        else:
            output_result = result
        return output_result

    def __round_target_position(self, rtid_vec, ideal_position_vec):
        if self.__comdty_universe is False:
            position_vec = np.array(ideal_position_vec)
            for i in xrange(len(ideal_position_vec)):
                if -const.kFillSizeDivisor < ideal_position_vec[i] < const.kFillSizeDivisor:
                    position_vec[i] = 0.0
            round_target_position_vec = np.round(position_vec / const.kFillSizeDivisor) *\
                                        const.kFillSizeDivisor
        else:
            position_vec = np.array(ideal_position_vec)
            for i in xrange(len(ideal_position_vec)):
                rtid = rtid_vec[i]
                trading_unit = self.__secinfo_map[rtid].trading_unit
                if -trading_unit < ideal_position_vec[i] < trading_unit:
                    position_vec[i] = 0.0
                else:
                    position_vec[i] = np.round(position_vec[i] / trading_unit) * trading_unit
            round_target_position_vec = np.array(position_vec)
        return round_target_position_vec

    @latency
    def __pre_calculate(self):
        for active_opt_model in self.__active_opt_model_list:
            active_opt_model.pre_calculate()

    def __limit_target_position(self, current_position_vec, position_vec):
        upper_limit_vec = self.__instrument_penalty_model.target_upper_limit_vec
        lower_limit_vec = self.__instrument_penalty_model.target_lower_limit_vec
        limited_target_position_vec = position_vec.copy()
        for i in xrange(len(position_vec)):
            upper_limit_vec[i] = current_position_vec[i] \
                if current_position_vec[i] > upper_limit_vec[i] else upper_limit_vec[i]
            lower_limit_vec[i] = current_position_vec[i] \
                if current_position_vec[i] < lower_limit_vec[i] else lower_limit_vec[i]

        for i in xrange(len(position_vec)):
            limited_target_position_vec[i] = upper_limit_vec[i] \
                if position_vec[i] > upper_limit_vec[i] else lower_limit_vec[i] \
                   if position_vec[i] < lower_limit_vec[i] else position_vec[i]
        return limited_target_position_vec

    def __check_target_position(self, current_position, target_position):
        if self.__delta_dollar_position_limit is not None:
            price_array = self.__snapshot_summary.ordered_price_array
            delta_position = np.abs(target_position - current_position)
            delta_dollar_position = delta_position * price_array
            checked_target_position = np.zeros(len(current_position))
            for i in xrange(len(current_position)):
                checked_target_position[i] = target_position[i] \
                    if delta_dollar_position[i] >= self.__delta_dollar_position_limit \
                       else current_position[i]
            return checked_target_position
        return target_position

    def __recovery(self):
        checkpoint_collector = ManagerHolder().get_manager('CheckpointCollector')
        checkpoint_epoch_usecond = checkpoint_collector.checkpoint_epoch_usecond
        live_optimizer_dir = Config().get_config('Live.OptimizerDir')
        optimizer_files_pattern = live_optimizer_dir + '/optimizer.*.csv'
        optimizer_file_list = glob.glob(optimizer_files_pattern)
        time_optimizer_file_dict = {}
        for optimizer_file in optimizer_file_list:
            epoch_usecond = os.path.basename(optimizer_file).split('.')[1]
            epoch_usecond = int(epoch_usecond.strip())
            time_optimizer_file_dict[epoch_usecond] = optimizer_file

        today_open_epoch_usecond = self.__timer_manager.today_open_timestamp().usecond_since_epoch
        if self.__approximate_sqrt_decay is True and today_open_epoch_usecond != checkpoint_epoch_usecond:
            self.__rmi_recorder.recovery_approximate_sqrt_live_rmi(checkpoint_epoch_usecond)
            
        epoch_usecond_list = sorted(time_optimizer_file_dict.keys())
        for epoch_usecond in epoch_usecond_list:
            optimizer_file = time_optimizer_file_dict[epoch_usecond]
            if epoch_usecond <= checkpoint_epoch_usecond:
                optimizer_reader = CsvReader(optimizer_file)
                for optimizer_row in optimizer_reader.content:
                    rtid = int(optimizer_row['RTId'])
                    target_position = float(optimizer_row['TargetQty'])
                    self.__position_recorder.set_recovery_position(rtid, target_position)
                    if self.__approximate_sqrt_decay is False:
                        rmi = float(optimizer_row['RMI'])
                        self.__rmi_recorder.set_post_rmi(rtid, rmi)
                optimizer_reader.close()
                print 'load optimizer file ', optimizer_file
            else:
                print 'remove optimizer file ', optimizer_file
                os.remove(optimizer_file)
        self.__last_optimizer_trade_usecond = self.__timer_manager.epoch_usecond_to_trade_usecond(
            checkpoint_epoch_usecond)

    def update_forecast(self):
        self.__forecast_consolidation.init_new_sampling()

    def eod_update(self):
        if self.__accounting_manager is not None:
            self.__accounting_manager.eod_update()
    def resend(self):
        self.__snapshot_summary.update_summary_data()
        self.__ordered_current_position_array = np.array(self.__position_recorder.get_position_list(
            self.__snapshot_summary.ordered_trade_universe_rtid_list))
        target_position_array = self.__ordered_current_position_array.copy()
        if self.__execution_manager is not None:
            self.__execution_manager.send_optimizer_target_position(
                self.__snapshot_summary.ordered_trade_universe_rtid_list,
                self.__ordered_current_position_array,
                target_position_array)
            self.__execution_manager.clear_cached_target_position()

    def update_optimizer(self, end_epoch_usecond):
        optimizer_filename = self.__optimizer_dir + '/optimizer.' + str(end_epoch_usecond) + '.csv'
        optimizer_writer = CsvWriter(optimizer_filename, self.__dump_headers)
        optimizer_writer.write_header()

        now_trade_usecond = self.__timer_manager.epoch_usecond_to_trade_usecond(
            end_epoch_usecond)
        if self.__residual_market_impact_model is not None:
            self.__residual_market_impact_model.init_new_sampling(
                now_trade_usecond - self.__last_optimizer_trade_usecond)

        self.__snapshot_summary.update_summary_data()
        if self.__capital_observer is not None:
            self.__capital_observer.update()
        self.__suspension_observer.update_suspension_data()
        self.__advlimit_observer.update_advlimit_data()
        self.__dollarlimit_observer.update_dollarlimit_data()
        self.__sharelimit_observer.update_sharelimit_data()
        if self.__tplus1_observer is not None:
            self.__tplus1_observer.update_tplus1_data()
        if self.__directed_trade_observer is not None:
            self.__directed_trade_observer.update_directed_trade_data()
        if self.__updownlimit_observer is not None:
            self.__updownlimit_observer.update_updown_limit_data()
        if self.__position_limit_observer is not None:
            self.__position_limit_observer.update_limit_data()
        if self.__manual_position_limit_observer is not None:
            self.__manual_position_limit_observer.update_manual_pos_limit_data()

        self.__trade_rtid_set = self.__snapshot_summary.trade_universe_rtid_set
        self.__ordered_price_array = self.__snapshot_summary.ordered_price_array
             
        self.__ordered_current_position_array = np.array(self.__position_recorder.get_position_list(
            self.__snapshot_summary.ordered_trade_universe_rtid_list))

        if self.__ignore_suspend is True:
            self.__effective_rtid_list = []
            self.__effective_idx_list = []
            self.__fill_gap_rtid_list = []
            self.__fill_gap_idx_list = []
            self.__idx_pos_dict = {}
            m = 0
            for rtid in self.__snapshot_summary.ordered_trade_universe_rtid_list:
                secinfo = self.__secinfo_map[rtid]
                if secinfo.suspend is True:
                    self.__fill_gap_rtid_list.append(rtid)
                    self.__fill_gap_idx_list.append(m)
                    self.__idx_pos_dict[m] = self.__ordered_current_position_array[m]
                    m += 1
                    continue
                calendar = self.__timer_manager.rtid_calendar(rtid)
                if self.__load_calendar_dict is True and \
                   not calendar.is_optimizer_trading_time(end_epoch_usecond):
                    self.__fill_gap_rtid_list.append(rtid)
                    self.__fill_gap_idx_list.append(m)
                    self.__idx_pos_dict[m] = self.__ordered_current_position_array[m]
                    m += 1
                    continue
                self.__effective_rtid_list.append(rtid)
                self.__effective_idx_list.append(m)
                m += 1
            print 'effective rtid length ', len(self.__effective_rtid_list), len(self.__idx_pos_dict), self.__timer_manager.timenow_str(), len(self.__snapshot_summary.ordered_trade_universe_rtid_list)

        self.__pre_calculate()

        res = self.optimize()
        fde_vec = self.fde(res, force_all = True)
        limited_target_position_vec = self.__limit_target_position(
            self.__ordered_current_position_array, res)
        ordered_trade_universe_rtid_list = self.__snapshot_summary.ordered_trade_universe_rtid_list

        round_target_position_vec = self.__round_target_position(
            self.__snapshot_summary.ordered_trade_universe_rtid_list,
            limited_target_position_vec)
        checked_target_position_vec = self.__check_target_position(
            self.__ordered_current_position_array, round_target_position_vec)

        target_info_summary = self.__execution_manager.send_optimizer_target_position(
                ordered_trade_universe_rtid_list, self.__ordered_current_position_array,
                checked_target_position_vec)
        executor_target_info_list = target_info_summary.target_info_list
        #self.__execution_manager.clear_cached_target_position()
        filled_target_info_dict = self.__accounting_manager.live_fill(
            end_epoch_usecond, executor_target_info_list,
            now_trade_usecond - self.__last_optimizer_trade_usecond)
        
        filled_target_position_vec = np.full(len(ordered_trade_universe_rtid_list), 0.0)
        for i in xrange(len(ordered_trade_universe_rtid_list)):
            rtid = ordered_trade_universe_rtid_list[i]
            filled_target_position = filled_target_info_dict[rtid].filled_position
            filled_target_position_vec[i] = filled_target_position

        if self.__residual_market_impact_model is not None and self.__rmi_recorder is not None:
            trade_usecond = self.__timer_manager.span_trade_usecond()
            delta_position_vec = filled_target_position_vec - self.__ordered_current_position_array
            if self.__residual_market_impact_model.sqrt_decay is True:
                for i in xrange(len(ordered_trade_universe_rtid_list)):
                    delta_position = delta_position_vec[i]
                    if delta_position == 0.0:
                        continue
                    a2 = self.__residual_market_impact_model.a2_vec[i]
                    rtid = ordered_trade_universe_rtid_list[i]
                    self.__rmi_recorder.set_realtime_rmi_components(rtid, trade_usecond, a2, delta_position)
            elif self.__residual_market_impact_model.approximate_sqrt_decay is True:
                a_vec = self.__residual_market_impact_model.a_vec
                hl_vec = self.__residual_market_impact_model.hl_vec
                for i in xrange(len(ordered_trade_universe_rtid_list)):
                    delta_position = delta_position_vec[i]
                    if delta_position == 0.0:
                        continue
                    rtid = ordered_trade_universe_rtid_list[i]
                    a2 = self.__residual_market_impact_model.a2_vec[i]
                    addend_vec = a2 * (abs(delta_position) ** 0.5) * np.sign(delta_position) \
                                 * self.__residual_market_impact_model.rmi_multiplier \
                                 * self.__residual_market_impact_model.a_vec \
                                 * np.exp(1.0 / self.__residual_market_impact_model.hl_vec)
                    self.__rmi_recorder.add_approximate_update(rtid, trade_usecond, addend_vec)
            else:
                addend_vec = self.__residual_market_impact_model.a2_vec * (abs(delta_position_vec) ** 0.5) \
                             * np.sign(delta_position_vec) * self.__residual_market_impact_model.rmi_multiplier
                self.__rmi_recorder.add_update(self.__snapshot_summary.ordered_trade_universe_rtid_list,
                                               addend_vec)

        iteration = self.__iteration_num
        self.__iteration_num = 0
        self.__position_recorder.set_position_list(filled_target_info_dict)

        short_mktval = 0.0
        long_mktval = 0.0
        abs_mktval = 0.0
        for i in xrange(len(ordered_trade_universe_rtid_list)):
            row = {}
            rtid = ordered_trade_universe_rtid_list[i]
            accounting_price = self.__snapshot_summary.accounting_price(rtid)
            mktval = filled_target_position_vec[i] * accounting_price
            row['RTId'] = rtid
            secinfo = self.__secinfo_map[rtid]
            uid = secinfo.uid
            eid = secinfo.eid
            trading_unit = secinfo.trading_unit
            exchange = secinfo.exchange
            row['Eid'] = eid
            row['Exchange'] = exchange
            row['Uid'] = uid
            exchange_enum = -1
            if exchange == 'CZC':
                exchange_enum = 5
            elif exchange == 'DCE':
                exchange_enum = 4
            elif exchange == 'SHF':
                exchange_enum = 3
            row['ExchangeEnum'] = exchange_enum
            row['Uid'] = self.__secinfo_map[rtid].uid
            row['DateTime'] = self.__timer_manager.timenow_str()
            row['MicroSecondSinceTrade'] = self.__timer_manager.now_trade_usecond()
            current_qty = self.__ordered_current_position_array[i]
            row['CurrentQty'] = current_qty
            row['IdealQty'] = res[i]
            row['FdeSum'] = fde_vec[i]
            target_position = filled_target_position_vec[i]
            row['TargetQty'] = target_position
            row['ExecutionQty'] = target_position / trading_unit
            row['Iteration'] = iteration
            row['OptimizerBeginTradeUsecond'] = self.__last_optimizer_trade_usecond
            row['OptimizerEndTradeUsecond'] = now_trade_usecond
            row['OptimizerClosePrice'] = self.__snapshot_summary.accounting_price(rtid)
            if self.__is_combine is True:
                for pid, header in self.__pid_current_list:
                    row[header] = target_info_summary.pid_current_position_dict[pid][i]
                for pid, position_header, mktval_header in self.__pid_target_list:
                    tg_position = target_info_summary.pid_target_position_dict[pid][i]
                    row[position_header] = tg_position
                    row[mktval_header] = tg_position * accounting_price

            row['OptimizerMktVal'] = mktval
            if mktval > 0.0:
                long_mktval += mktval
            else:
                short_mktval += mktval
            abs_mktval += abs(mktval)
            for active_opt_model in self.__active_opt_model_list:
                row[active_opt_model.__class__.__name__] = active_opt_model.fde_vec[i]
            row['ForecastConsolidation'] \
                = self.__forecast_opt_model.forecast_consolidation_forecast_vec[i]
            if self.__approximate_sqrt_decay is False:
                row['RMI'] = self.__rmi_recorder.post_rmi(rtid)
            else:
                row['RMI'] = 0.0
            for model, vec in self.__forecast_opt_model.active_model_forecast_vec_map.items():
                row[model.__class__.__name__] = vec[i]
            optimizer_writer.write_row(row)
            if target_position - current_qty != 0.0:
                log.critical('comdty target position change: uid ' + str(uid) + ' current ' \
                             + str(current_qty) + ' target '  + str(target_position) \
                             + ' delta ' + str(target_position - current_qty))

        optimizer_writer.flush()
        optimizer_writer.close()
        log.critical('comdty long market val: ' + str(long_mktval) + ' short market val: ' \
                     + str(short_mktval) + ' total abs market val: ' + str(abs_mktval))

        factor_filename = self.__optimizer_dir + '/factor.' + str(end_epoch_usecond) + '.csv'
        factor_writer = CsvWriter(factor_filename, self.__factor_dump_headers)
        factor_writer.write_header()
        for factor_id in self.__factor_snapshot_summary.factor_id_list:
            row = {}
            row['FactorId'] = factor_id
            row['FactorName'] = self.__factor_id_to_name_map[factor_id]
            row['DateTime'] = self.__timer_manager.timenow_str()
            row['MicroSecondSinceTrade'] = self.__timer_manager.now_trade_usecond()
            row['FactorRet'] = self.__factor_snapshot_summary.factor_ret_to_prev_date(factor_id)
            factor_writer.write_row(row)
        factor_writer.flush()
        factor_writer.close()

        rtid_factor_filename = self.__optimizer_dir + '/rtid_factor.' + str(end_epoch_usecond) + '.csv'
        rtid_factor_writer = CsvWriter(rtid_factor_filename, self.__rtid_factor_dump_headers)
        rtid_factor_writer.write_header()
        for rtid in self.__trading_comdty_rtid_list:
            row = {}
            row['RTId'] = rtid
            row['Uid'] = self.__secinfo_map[rtid].uid
            row['DateTime'] = self.__timer_manager.timenow_str()
            market_beta = self.__snapshot_summary.market_beta_map[rtid] \
                          if self.__snapshot_summary.market_beta_map.has_key(rtid) \
                             else 1.0
            row['MarketBeta'] = market_beta
            industry_beta = self.__snapshot_summary.industry_beta_map[rtid] \
                            if self.__snapshot_summary.industry_beta_map.has_key(rtid) else 1.0
            row['IndustryBeta'] = industry_beta
            rtid_factor_writer.write_row(row)
        rtid_factor_writer.flush()
        rtid_factor_writer.close()
        if self.__approximate_sqrt_decay is True:
            self.__rmi_recorder.dump_approximate_sqrt_live_rmi(end_epoch_usecond)
        temp_filename = self.__optimizer_dir + '/temp'
        temp_file = open(temp_filename, 'wb')
        temp_file.write(str(end_epoch_usecond))
        temp_file.flush()
        temp_file.close()
        done_filename = self.__meta_dir + '/optimizer.meta'
        os.rename(temp_filename, done_filename)
        self.__last_optimizer_trade_usecond = now_trade_usecond


