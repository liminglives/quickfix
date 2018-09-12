#ifndef FIX42_SETTLEMENTRESULTCOMFIRMSTATUSREQUEST_H
#define FIX42_SETTLEMENTRESULTCOMFIRMSTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class SettlementResultComfirmStatusRequest : public Message
  {
  public:
    SettlementResultComfirmStatusRequest() : Message(MsgType()) {}
    SettlementResultComfirmStatusRequest(const FIX::Message& m) : Message(m) {}
    SettlementResultComfirmStatusRequest(const Message& m) : Message(m) {}
    SettlementResultComfirmStatusRequest(const SettlementResultComfirmStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF017"); }

    SettlementResultComfirmStatusRequest(
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
    FIELD_SET(*this, FIX::SettlementDate);
    FIELD_SET(*this, FIX::SecurityExchange);
  };

}

#endif
