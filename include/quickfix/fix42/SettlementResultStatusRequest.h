#ifndef FIX42_SETTLEMENTRESULTSTATUSREQUEST_H
#define FIX42_SETTLEMENTRESULTSTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class SettlementResultStatusRequest : public Message
  {
  public:
    SettlementResultStatusRequest() : Message(MsgType()) {}
    SettlementResultStatusRequest(const FIX::Message& m) : Message(m) {}
    SettlementResultStatusRequest(const Message& m) : Message(m) {}
    SettlementResultStatusRequest(const SettlementResultStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF013"); }

    SettlementResultStatusRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::SettlementDate& aSettlementDate,
      const FIX::SecurityExchange& aSecurityExchange )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aSettlementDate);
      set(aSecurityExchange);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::SettlementDate);
    FIELD_SET(*this, FIX::SecurityExchange);
  };

}

#endif
