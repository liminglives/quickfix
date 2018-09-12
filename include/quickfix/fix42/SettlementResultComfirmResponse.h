#ifndef FIX42_SETTLEMENTRESULTCOMFIRMRESPONSE_H
#define FIX42_SETTLEMENTRESULTCOMFIRMRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class SettlementResultComfirmResponse : public Message
  {
  public:
    SettlementResultComfirmResponse() : Message(MsgType()) {}
    SettlementResultComfirmResponse(const FIX::Message& m) : Message(m) {}
    SettlementResultComfirmResponse(const Message& m) : Message(m) {}
    SettlementResultComfirmResponse(const SettlementResultComfirmResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF016"); }

    SettlementResultComfirmResponse(
      const FIX::RequestID& aRequestID,
      const FIX::SettlementConfirmResult& aSettlementConfirmResult,
      const FIX::SecurityExchange& aSecurityExchange )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aSettlementConfirmResult);
      set(aSecurityExchange);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::SettlementDate);
    FIELD_SET(*this, FIX::SettlementConfirmResult);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
