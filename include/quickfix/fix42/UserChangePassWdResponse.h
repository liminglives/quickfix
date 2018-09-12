#ifndef FIX42_USERCHANGEPASSWDRESPONSE_H
#define FIX42_USERCHANGEPASSWDRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class UserChangePassWdResponse : public Message
  {
  public:
    UserChangePassWdResponse() : Message(MsgType()) {}
    UserChangePassWdResponse(const FIX::Message& m) : Message(m) {}
    UserChangePassWdResponse(const Message& m) : Message(m) {}
    UserChangePassWdResponse(const UserChangePassWdResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF006"); }

    UserChangePassWdResponse(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::ChangePWResult& aChangePWResult )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aChangePWResult);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::ChangePWResult);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
