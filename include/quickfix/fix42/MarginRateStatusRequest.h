#ifndef FIX42_MARGINRATESTATUSREQUEST_H
#define FIX42_MARGINRATESTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class MarginRateStatusRequest : public Message
  {
  public:
    MarginRateStatusRequest() : Message(MsgType()) {}
    MarginRateStatusRequest(const FIX::Message& m) : Message(m) {}
    MarginRateStatusRequest(const Message& m) : Message(m) {}
    MarginRateStatusRequest(const MarginRateStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF018"); }

    MarginRateStatusRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::VarietyCode& aVarietyCode,
      const FIX::SecurityExchange& aSecurityExchange )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aVarietyCode);
      set(aSecurityExchange);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::VarietyCode);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::SecurityExchange);
  };

}

#endif
