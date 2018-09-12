#ifndef FIX42_SETTLEMENTRESULTSTATUSRESPONSE_H
#define FIX42_SETTLEMENTRESULTSTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class SettlementResultStatusResponse : public Message
  {
  public:
    SettlementResultStatusResponse() : Message(MsgType()) {}
    SettlementResultStatusResponse(const FIX::Message& m) : Message(m) {}
    SettlementResultStatusResponse(const Message& m) : Message(m) {}
    SettlementResultStatusResponse(const SettlementResultStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF014"); }

    SettlementResultStatusResponse(
      const FIX::RequestID& aRequestID,
      const FIX::SettlementDate& aSettlementDate,
      const FIX::Text& aText,
      const FIX::SecurityExchange& aSecurityExchange )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aSettlementDate);
      set(aText);
      set(aSecurityExchange);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::SettlementDate);
    FIELD_SET(*this, FIX::TotalRetNum);
    FIELD_SET(*this, FIX::PresentRetNum);
    FIELD_SET(*this, FIX::NextFlag);
    FIELD_SET(*this, FIX::Text);
    FIELD_SET(*this, FIX::SecurityExchange);
  };

}

#endif
