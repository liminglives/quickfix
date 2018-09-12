#ifndef FIX42_MARKETDATASTATUSCANCELRESPONSE_H
#define FIX42_MARKETDATASTATUSCANCELRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class MarketDataStatusCancelResponse : public Message
  {
  public:
    MarketDataStatusCancelResponse() : Message(MsgType()) {}
    MarketDataStatusCancelResponse(const FIX::Message& m) : Message(m) {}
    MarketDataStatusCancelResponse(const Message& m) : Message(m) {}
    MarketDataStatusCancelResponse(const MarketDataStatusCancelResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF029"); }

    MarketDataStatusCancelResponse(
      const FIX::MDReqID& aMDReqID )
    : Message(MsgType())
    {
      set(aMDReqID);
    }

    FIELD_SET(*this, FIX::MDReqID);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
