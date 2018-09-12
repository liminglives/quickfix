#ifndef FIX42_CUSTOMERCAPITALSTATUSREQUEST_H
#define FIX42_CUSTOMERCAPITALSTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class CustomerCapitalStatusRequest : public Message
  {
  public:
    CustomerCapitalStatusRequest() : Message(MsgType()) {}
    CustomerCapitalStatusRequest(const FIX::Message& m) : Message(m) {}
    CustomerCapitalStatusRequest(const Message& m) : Message(m) {}
    CustomerCapitalStatusRequest(const CustomerCapitalStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF022"); }

    CustomerCapitalStatusRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::Currency);
  };

}

#endif
