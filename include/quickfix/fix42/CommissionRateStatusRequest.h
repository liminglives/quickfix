#ifndef FIX42_COMMISSIONRATESTATUSREQUEST_H
#define FIX42_COMMISSIONRATESTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class CommissionRateStatusRequest : public Message
  {
  public:
    CommissionRateStatusRequest() : Message(MsgType()) {}
    CommissionRateStatusRequest(const FIX::Message& m) : Message(m) {}
    CommissionRateStatusRequest(const Message& m) : Message(m) {}
    CommissionRateStatusRequest(const CommissionRateStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF020"); }

    CommissionRateStatusRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::SecurityExchange& aSecurityExchange )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aSecurityExchange);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::SecurityExchange);
  };

}

#endif
