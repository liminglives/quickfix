#ifndef FIX42_USERLOGOUTREQUEST_H
#define FIX42_USERLOGOUTREQUEST_H

#include "Message.h"

namespace FIX42
{

  class UserLogoutRequest : public Message
  {
  public:
    UserLogoutRequest() : Message(MsgType()) {}
    UserLogoutRequest(const FIX::Message& m) : Message(m) {}
    UserLogoutRequest(const Message& m) : Message(m) {}
    UserLogoutRequest(const UserLogoutRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF003"); }

    UserLogoutRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
  };

}

#endif
