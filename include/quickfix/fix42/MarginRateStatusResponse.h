#ifndef FIX42_MARGINRATESTATUSRESPONSE_H
#define FIX42_MARGINRATESTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class MarginRateStatusResponse : public Message
  {
  public:
    MarginRateStatusResponse() : Message(MsgType()) {}
    MarginRateStatusResponse(const FIX::Message& m) : Message(m) {}
    MarginRateStatusResponse(const Message& m) : Message(m) {}
    MarginRateStatusResponse(const MarginRateStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF019"); }

    MarginRateStatusResponse(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::SpecLongMarginRate& aSpecLongMarginRate,
      const FIX::SpecShortMarginRate& aSpecShortMarginRate,
      const FIX::HedgeLongMarginRate& aHedgeLongMarginRate,
      const FIX::HedgeShortMarginRate& aHedgeShortMarginRate,
      const FIX::SpecLongMarginAmt& aSpecLongMarginAmt,
      const FIX::SpecShortMarginAmt& aSpecShortMarginAmt,
      const FIX::HedgeLongMarginAmt& aHedgeLongMarginAmt,
      const FIX::HedgeShortMarginAmt& aHedgeShortMarginAmt,
      const FIX::SecurityExchange& aSecurityExchange )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aSpecLongMarginRate);
      set(aSpecShortMarginRate);
      set(aHedgeLongMarginRate);
      set(aHedgeShortMarginRate);
      set(aSpecLongMarginAmt);
      set(aSpecShortMarginAmt);
      set(aHedgeLongMarginAmt);
      set(aHedgeShortMarginAmt);
      set(aSecurityExchange);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::SpecLongMarginRate);
    FIELD_SET(*this, FIX::SpecShortMarginRate);
    FIELD_SET(*this, FIX::HedgeLongMarginRate);
    FIELD_SET(*this, FIX::HedgeShortMarginRate);
    FIELD_SET(*this, FIX::SpecLongMarginAmt);
    FIELD_SET(*this, FIX::SpecShortMarginAmt);
    FIELD_SET(*this, FIX::HedgeLongMarginAmt);
    FIELD_SET(*this, FIX::HedgeShortMarginAmt);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
