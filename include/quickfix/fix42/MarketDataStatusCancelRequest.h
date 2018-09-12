#ifndef FIX42_MARKETDATASTATUSCANCELREQUEST_H
#define FIX42_MARKETDATASTATUSCANCELREQUEST_H

#include "Message.h"

namespace FIX42
{

  class MarketDataStatusCancelRequest : public Message
  {
  public:
    MarketDataStatusCancelRequest() : Message(MsgType()) {}
    MarketDataStatusCancelRequest(const FIX::Message& m) : Message(m) {}
    MarketDataStatusCancelRequest(const Message& m) : Message(m) {}
    MarketDataStatusCancelRequest(const MarketDataStatusCancelRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF028"); }

    MarketDataStatusCancelRequest(
      const FIX::MDReqID& aMDReqID,
      const FIX::SubscriptionRequestType& aSubscriptionRequestType )
    : Message(MsgType())
    {
      set(aMDReqID);
      set(aSubscriptionRequestType);
    }

    FIELD_SET(*this, FIX::MDReqID);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::SubscriptionRequestType);
  };

}

#endif
