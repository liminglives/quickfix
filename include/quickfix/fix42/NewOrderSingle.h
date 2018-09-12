#ifndef FIX42_NEWORDERSINGLE_H
#define FIX42_NEWORDERSINGLE_H

#include "Message.h"

namespace FIX42
{

  class NewOrderSingle : public Message
  {
  public:
    NewOrderSingle() : Message(MsgType()) {}
    NewOrderSingle(const FIX::Message& m) : Message(m) {}
    NewOrderSingle(const Message& m) : Message(m) {}
    NewOrderSingle(const NewOrderSingle& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("D"); }

    NewOrderSingle(
      const FIX::ClOrdID& aClOrdID,
      const FIX::HandlInst& aHandlInst,
      const FIX::Symbol& aSymbol,
      const FIX::Side& aSide,
      const FIX::TransactTime& aTransactTime,
      const FIX::OrdType& aOrdType )
    : Message(MsgType())
    {
      set(aClOrdID);
      set(aHandlInst);
      set(aSymbol);
      set(aSide);
      set(aTransactTime);
      set(aOrdType);
    }

    FIELD_SET(*this, FIX::ClOrdID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::ExecBroker);
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::SettlmntTyp);
    FIELD_SET(*this, FIX::FutSettDate);
    FIELD_SET(*this, FIX::HandlInst);
    FIELD_SET(*this, FIX::ExecInst);
    FIELD_SET(*this, FIX::MinQty);
    FIELD_SET(*this, FIX::MaxFloor);
    FIELD_SET(*this, FIX::ExDestination);
    FIELD_SET(*this, FIX::ProcessCode);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SymbolSfx);
    FIELD_SET(*this, FIX::SecurityID);
    FIELD_SET(*this, FIX::IDSource);
    FIELD_SET(*this, FIX::SecurityType);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::MaturityDay);
    FIELD_SET(*this, FIX::PutOrCall);
    FIELD_SET(*this, FIX::StrikePrice);
    FIELD_SET(*this, FIX::OptAttribute);
    FIELD_SET(*this, FIX::ContractMultiplier);
    FIELD_SET(*this, FIX::CouponRate);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::Issuer);
    FIELD_SET(*this, FIX::EncodedIssuerLen);
    FIELD_SET(*this, FIX::EncodedIssuer);
    FIELD_SET(*this, FIX::SecurityDesc);
    FIELD_SET(*this, FIX::EncodedSecurityDescLen);
    FIELD_SET(*this, FIX::EncodedSecurityDesc);
    FIELD_SET(*this, FIX::PrevClosePx);
    FIELD_SET(*this, FIX::Side);
    FIELD_SET(*this, FIX::LocateReqd);
    FIELD_SET(*this, FIX::TransactTime);
    FIELD_SET(*this, FIX::OrderQty);
    FIELD_SET(*this, FIX::CashOrderQty);
    FIELD_SET(*this, FIX::OrdType);
    FIELD_SET(*this, FIX::Price);
    FIELD_SET(*this, FIX::StopPx);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::ComplianceID);
    FIELD_SET(*this, FIX::SolicitedFlag);
    FIELD_SET(*this, FIX::IOIid);
    FIELD_SET(*this, FIX::QuoteID);
    FIELD_SET(*this, FIX::TimeInForce);
    FIELD_SET(*this, FIX::EffectiveTime);
    FIELD_SET(*this, FIX::ExpireDate);
    FIELD_SET(*this, FIX::ExpireTime);
    FIELD_SET(*this, FIX::GTBookingInst);
    FIELD_SET(*this, FIX::Commission);
    FIELD_SET(*this, FIX::CommType);
    FIELD_SET(*this, FIX::Rule80A);
    FIELD_SET(*this, FIX::ForexReq);
    FIELD_SET(*this, FIX::SettlCurrency);
    FIELD_SET(*this, FIX::Text);
    FIELD_SET(*this, FIX::EncodedTextLen);
    FIELD_SET(*this, FIX::EncodedText);
    FIELD_SET(*this, FIX::FutSettDate2);
    FIELD_SET(*this, FIX::OrderQty2);
    FIELD_SET(*this, FIX::OpenClose);
    FIELD_SET(*this, FIX::CoveredOrUncovered);
    FIELD_SET(*this, FIX::CustomerOrFirm);
    FIELD_SET(*this, FIX::MaxShow);
    FIELD_SET(*this, FIX::PegDifference);
    FIELD_SET(*this, FIX::DiscretionInst);
    FIELD_SET(*this, FIX::DiscretionOffset);
    FIELD_SET(*this, FIX::ClearingFirm);
    FIELD_SET(*this, FIX::ClearingAccount);
    FIELD_SET(*this, FIX::HedgeFlag);
    FIELD_SET(*this, FIX::TouchCondition);
    FIELD_SET(*this, FIX::PriceType);
    FIELD_SET(*this, FIX::CloseFlag);
    FIELD_SET(*this, FIX::StrategyType);
    FIELD_SET(*this, FIX::StrategyStatus);
    FIELD_SET(*this, FIX::StartTime);
    FIELD_SET(*this, FIX::EndTime);
    FIELD_SET(*this, FIX::ParticipationRate);
    FIELD_SET(*this, FIX::Style);
    FIELD_SET(*this, FIX::RefPrice);
    FIELD_SET(*this, FIX::OPG);
    FIELD_SET(*this, FIX::MOC);
    FIELD_SET(*this, FIX::MinDisplaySize);
    FIELD_SET(*this, FIX::CountEligibleVolumewithinLimitPrice);
    FIELD_SET(*this, FIX::ResetEligibleVolumewithinLimitPrice);
    FIELD_SET(*this, FIX::MaxPriceLevels);
    FIELD_SET(*this, FIX::MaxOrdersPerLevels);
    FIELD_SET(*this, FIX::RelativePriceLimitBase);
    FIELD_SET(*this, FIX::RelativePriceLimitType);
    FIELD_SET(*this, FIX::RelativePriceLimitOffset);
    FIELD_SET(*this, FIX::AMOpenPercent);
    FIELD_SET(*this, FIX::PMClosePercent);
    FIELD_SET(*this, FIX::AMPercent);
    FIELD_SET(*this, FIX::SerialNum);
    FIELD_SET(*this, FIX::CumQty);
    FIELD_SET(*this, FIX::GrossTradeAmt);
    FIELD_SET(*this, FIX::RegId);
    FIELD_SET(*this, FIX::BatchNum);
    FIELD_SET(*this, FIX::UserId);
    FIELD_SET(*this, FIX::MacAddress);
    FIELD_SET(*this, FIX::OrigClOrdID);
    FIELD_SET(*this, FIX::QtyMode);
    FIELD_SET(*this, FIX::SecondaryOrderID);
    FIELD_SET(*this, FIX::NoAllocs);
    class NoAllocs: public FIX::Group
    {
    public:
    NoAllocs() : FIX::Group(78,79,FIX::message_order(79,80,0)) {}
      FIELD_SET(*this, FIX::AllocAccount);
      FIELD_SET(*this, FIX::AllocShares);
    };
    FIELD_SET(*this, FIX::NoTradingSessions);
    class NoTradingSessions: public FIX::Group
    {
    public:
    NoTradingSessions() : FIX::Group(386,336,FIX::message_order(336,0)) {}
      FIELD_SET(*this, FIX::TradingSessionID);
    };
  };

}

#endif
