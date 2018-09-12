#ifndef FIX42_COMMISSIONRATESTATUSRESPONSE_H
#define FIX42_COMMISSIONRATESTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class CommissionRateStatusResponse : public Message
  {
  public:
    CommissionRateStatusResponse() : Message(MsgType()) {}
    CommissionRateStatusResponse(const FIX::Message& m) : Message(m) {}
    CommissionRateStatusResponse(const Message& m) : Message(m) {}
    CommissionRateStatusResponse(const CommissionRateStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF021"); }

    CommissionRateStatusResponse(
      const FIX::RequestID& aRequestID,
      const FIX::OpenCommissionRate& aOpenCommissionRate,
      const FIX::OpenCommissionAmt& aOpenCommissionAmt,
      const FIX::CloseCommissionRate& aCloseCommissionRate,
      const FIX::CloseCommissionAmt& aCloseCommissionAmt,
      const FIX::SecurityExchange& aSecurityExchange )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aOpenCommissionRate);
      set(aOpenCommissionAmt);
      set(aCloseCommissionRate);
      set(aCloseCommissionAmt);
      set(aSecurityExchange);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::OpenCommissionRate);
    FIELD_SET(*this, FIX::OpenCommissionAmt);
    FIELD_SET(*this, FIX::CloseCommissionRate);
    FIELD_SET(*this, FIX::CloseCommissionAmt);
    FIELD_SET(*this, FIX::CloseTdCommissionRate);
    FIELD_SET(*this, FIX::CloseTdCommissionAmt);
    FIELD_SET(*this, FIX::SettleFee);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
