#ifndef FIX42_ALLORDERSSTATUSREQUEST_H
#define FIX42_ALLORDERSSTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class AllOrdersStatusRequest : public Message
  {
  public:
    AllOrdersStatusRequest() : Message(MsgType()) {}
    AllOrdersStatusRequest(const FIX::Message& m) : Message(m) {}
    AllOrdersStatusRequest(const Message& m) : Message(m) {}
    AllOrdersStatusRequest(const AllOrdersStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF011"); }

    AllOrdersStatusRequest(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::SecurityExchange);
  };

}

#endif
