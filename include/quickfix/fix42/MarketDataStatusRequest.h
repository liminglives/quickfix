#ifndef FIX42_MARKETDATASTATUSREQUEST_H
#define FIX42_MARKETDATASTATUSREQUEST_H

#include "Message.h"

namespace FIX42
{

  class MarketDataStatusRequest : public Message
  {
  public:
    MarketDataStatusRequest() : Message(MsgType()) {}
    MarketDataStatusRequest(const FIX::Message& m) : Message(m) {}
    MarketDataStatusRequest(const Message& m) : Message(m) {}
    MarketDataStatusRequest(const MarketDataStatusRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF026"); }

    MarketDataStatusRequest(
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
