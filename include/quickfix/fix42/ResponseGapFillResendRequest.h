#ifndef FIX42_RESPONSEGAPFILLRESENDREQUEST_H
#define FIX42_RESPONSEGAPFILLRESENDREQUEST_H

#include "Message.h"

namespace FIX42
{

  class ResponseGapFillResendRequest : public Message
  {
  public:
    ResponseGapFillResendRequest() : Message(MsgType()) {}
    ResponseGapFillResendRequest(const FIX::Message& m) : Message(m) {}
    ResponseGapFillResendRequest(const Message& m) : Message(m) {}
    ResponseGapFillResendRequest(const ResponseGapFillResendRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF030"); }

    ResponseGapFillResendRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::GapMessageType& aGapMessageType,
      const FIX::GapStartNum& aGapStartNum,
      const FIX::GapEndNum& aGapEndNum )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aGapMessageType);
      set(aGapStartNum);
      set(aGapEndNum);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::GapMessageType);
    FIELD_SET(*this, FIX::GapStartNum);
    FIELD_SET(*this, FIX::GapEndNum);
  };

}

#endif
