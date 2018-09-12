#ifndef FIX42_MAXOPERATIONPOSITIONSTATUSREQUEST_H
#define FIX42_MAXOPERATIONPOSITIONSTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class MaxOperationPositionStatusRequest : public Message
  {
  public:
    MaxOperationPositionStatusRequest() : Message(MsgType()) {}
    MaxOperationPositionStatusRequest(const FIX::Message& m) : Message(m) {}
    MaxOperationPositionStatusRequest(const Message& m) : Message(m) {}
    MaxOperationPositionStatusRequest(const MaxOperationPositionStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF009"); }

    MaxOperationPositionStatusRequest(
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
    FIELD_SET(*this, FIX::Price);
    FIELD_SET(*this, FIX::HedgeFlag);
  };

}

#endif
