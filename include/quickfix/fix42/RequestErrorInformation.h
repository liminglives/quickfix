#ifndef FIX42_REQUESTERRORINFORMATION_H
#define FIX42_REQUESTERRORINFORMATION_H

#include "Message.h"

namespace FIX42
{

  class RequestErrorInformation : public Message
  {
  public:
    RequestErrorInformation() : Message(MsgType()) {}
    RequestErrorInformation(const FIX::Message& m) : Message(m) {}
    RequestErrorInformation(const Message& m) : Message(m) {}
    RequestErrorInformation(const RequestErrorInformation& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF033"); }

    RequestErrorInformation(
      const FIX::RequestMsgType& aRequestMsgType,
      const FIX::RequestID& aRequestID,
      const FIX::ErrorCode& aErrorCode,
      const FIX::Text& aText )
    : Message(MsgType())
    {
      set(aRequestMsgType);
      set(aRequestID);
      set(aErrorCode);
      set(aText);
    }

    FIELD_SET(*this, FIX::RequestMsgType);
    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ErrorCode);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
