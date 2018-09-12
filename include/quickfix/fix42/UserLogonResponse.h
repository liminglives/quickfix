#ifndef FIX42_USERLOGONRESPONSE_H
#define FIX42_USERLOGONRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class UserLogonResponse : public Message
  {
  public:
    UserLogonResponse() : Message(MsgType()) {}
    UserLogonResponse(const FIX::Message& m) : Message(m) {}
    UserLogonResponse(const Message& m) : Message(m) {}
    UserLogonResponse(const UserLogonResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF002"); }

    UserLogonResponse(
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
    FIELD_SET(*this, FIX::AccountName);
    FIELD_SET(*this, FIX::RiskLevel);
    FIELD_SET(*this, FIX::AdditionalMargin);
    FIELD_SET(*this, FIX::ClientSecuType);
    FIELD_SET(*this, FIX::Riskratio);
    FIELD_SET(*this, FIX::LastLogonIP);
    FIELD_SET(*this, FIX::LastLogonTime);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
