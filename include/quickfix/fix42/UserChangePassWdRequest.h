#ifndef FIX42_USERCHANGEPASSWDREQUEST_H
#define FIX42_USERCHANGEPASSWDREQUEST_H

#include "Message.h"

namespace FIX42
{

  class UserChangePassWdRequest : public Message
  {
  public:
    UserChangePassWdRequest() : Message(MsgType()) {}
    UserChangePassWdRequest(const FIX::Message& m) : Message(m) {}
    UserChangePassWdRequest(const Message& m) : Message(m) {}
    UserChangePassWdRequest(const UserChangePassWdRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF005"); }

    UserChangePassWdRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::PassWdType& aPassWdType,
      const FIX::OldPassWd& aOldPassWd,
      const FIX::NewPassWd& aNewPassWd )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aPassWdType);
      set(aOldPassWd);
      set(aNewPassWd);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::PassWdType);
    FIELD_SET(*this, FIX::OldPassWd);
    FIELD_SET(*this, FIX::NewPassWd);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
