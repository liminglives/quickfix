#ifndef FIX42_MAXOPERATIONPOSITIONSTATUSRESPONSE_H
#define FIX42_MAXOPERATIONPOSITIONSTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class MaxOperationPositionStatusResponse : public Message
  {
  public:
    MaxOperationPositionStatusResponse() : Message(MsgType()) {}
    MaxOperationPositionStatusResponse(const FIX::Message& m) : Message(m) {}
    MaxOperationPositionStatusResponse(const Message& m) : Message(m) {}
    MaxOperationPositionStatusResponse(const MaxOperationPositionStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF010"); }

    MaxOperationPositionStatusResponse(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::SecurityExchange& aSecurityExchange,
      const FIX::OpenClose& aOpenClose,
      const FIX::Side& aSide,
      const FIX::HedgeFlag& aHedgeFlag )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aSecurityExchange);
      set(aOpenClose);
      set(aSide);
      set(aHedgeFlag);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::OpenClose);
    FIELD_SET(*this, FIX::Side);
    FIELD_SET(*this, FIX::MaxOpenPosition);
    FIELD_SET(*this, FIX::MaxClosePosition);
    FIELD_SET(*this, FIX::MaxCloseTdPosition);
    FIELD_SET(*this, FIX::HedgeFlag);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
