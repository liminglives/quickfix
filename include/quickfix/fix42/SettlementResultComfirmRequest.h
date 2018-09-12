#ifndef FIX42_SETTLEMENTRESULTCOMFIRMREQUEST_H
#define FIX42_SETTLEMENTRESULTCOMFIRMREQUEST_H

#include "Message.h"

namespace FIX42
{

  class SettlementResultComfirmRequest : public Message
  {
  public:
    SettlementResultComfirmRequest() : Message(MsgType()) {}
    SettlementResultComfirmRequest(const FIX::Message& m) : Message(m) {}
    SettlementResultComfirmRequest(const Message& m) : Message(m) {}
    SettlementResultComfirmRequest(const SettlementResultComfirmRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF015"); }

    SettlementResultComfirmRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::SettlementConfirm& aSettlementConfirm,
      const FIX::SecurityExchange& aSecurityExchange )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aSettlementConfirm);
      set(aSecurityExchange);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::SettlementDate);
    FIELD_SET(*this, FIX::SettlementConfirm);
    FIELD_SET(*this, FIX::SecurityExchange);
  };

}

#endif
