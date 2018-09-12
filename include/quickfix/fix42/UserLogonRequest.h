#ifndef FIX42_USERLOGONREQUEST_H
#define FIX42_USERLOGONREQUEST_H

#include "Message.h"

namespace FIX42
{

  class UserLogonRequest : public Message
  {
  public:
    UserLogonRequest() : Message(MsgType()) {}
    UserLogonRequest(const FIX::Message& m) : Message(m) {}
    UserLogonRequest(const Message& m) : Message(m) {}
    UserLogonRequest(const UserLogonRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF001"); }

    UserLogonRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::EncryptMethod& aEncryptMethod,
      const FIX::LogonPasswd& aLogonPasswd )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aEncryptMethod);
      set(aLogonPasswd);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::EncryptMethod);
    FIELD_SET(*this, FIX::LogonPasswd);
    FIELD_SET(*this, FIX::IPAddress);
    FIELD_SET(*this, FIX::MacAddress);
  };

}

#endif
