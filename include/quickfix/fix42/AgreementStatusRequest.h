#ifndef FIX42_AGREEMENTSTATUSREQUEST_H
#define FIX42_AGREEMENTSTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class AgreementStatusRequest : public Message
  {
  public:
    AgreementStatusRequest() : Message(MsgType()) {}
    AgreementStatusRequest(const FIX::Message& m) : Message(m) {}
    AgreementStatusRequest(const Message& m) : Message(m) {}
    AgreementStatusRequest(const AgreementStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType(" UF024"); }

    AgreementStatusRequest(
      const FIX::RequestID& aRequestID )
    : Message(MsgType())
    {
      set(aRequestID);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SecurityExchange);
  };

}

#endif
