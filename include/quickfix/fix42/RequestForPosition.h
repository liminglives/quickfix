#ifndef FIX42_REQUESTFORPOSITION_H
#define FIX42_REQUESTFORPOSITION_H

#include "Message.h"

namespace FIX42
{

  class RequestForPosition : public Message
  {
  public:
    RequestForPosition() : Message(MsgType()) {}
    RequestForPosition(const FIX::Message& m) : Message(m) {}
    RequestForPosition(const Message& m) : Message(m) {}
    RequestForPosition(const RequestForPosition& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("URP"); }

    RequestForPosition(
      const FIX::Account& aAccount,
      const FIX::RequestID& aRequestID )
    : Message(MsgType())
    {
      set(aAccount);
      set(aRequestID);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::RequestID);
  };

}

#endif
