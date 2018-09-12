#ifndef FIX42_USERLOGOUTRESPONSE_H
#define FIX42_USERLOGOUTRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class UserLogoutResponse : public Message
  {
  public:
    UserLogoutResponse() : Message(MsgType()) {}
    UserLogoutResponse(const FIX::Message& m) : Message(m) {}
    UserLogoutResponse(const Message& m) : Message(m) {}
    UserLogoutResponse(const UserLogoutResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF004"); }

    UserLogoutResponse(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::LogonStatus& aLogonStatus )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aLogonStatus);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::LogonStatus);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
