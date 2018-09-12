#ifndef FIX42_POSITIONSTATUSREQUEST_H
#define FIX42_POSITIONSTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class PositionStatusRequest : public Message
  {
  public:
    PositionStatusRequest() : Message(MsgType()) {}
    PositionStatusRequest(const FIX::Message& m) : Message(m) {}
    PositionStatusRequest(const Message& m) : Message(m) {}
    PositionStatusRequest(const PositionStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF007"); }

    PositionStatusRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::Side);
  };

}

#endif
