#ifndef FIX42_REQUESTFORBALANCE_H
#define FIX42_REQUESTFORBALANCE_H

#include "Message.h"

namespace FIX42
{

  class RequestForBalance : public Message
  {
  public:
    RequestForBalance() : Message(MsgType()) {}
    RequestForBalance(const FIX::Message& m) : Message(m) {}
    RequestForBalance(const Message& m) : Message(m) {}
    RequestForBalance(const RequestForBalance& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("URB"); }

    RequestForBalance(
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
