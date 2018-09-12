#ifndef FIX42_MARKETDATASTATUSRESPONSE_H
#define FIX42_MARKETDATASTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class MarketDataStatusResponse : public Message
  {
  public:
    MarketDataStatusResponse() : Message(MsgType()) {}
    MarketDataStatusResponse(const FIX::Message& m) : Message(m) {}
    MarketDataStatusResponse(const Message& m) : Message(m) {}
    MarketDataStatusResponse(const MarketDataStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF027"); }

    MarketDataStatusResponse(
      const FIX::MDReqID& aMDReqID,
      const FIX::Symbol& aSymbol,
      const FIX::TradeDate& aTradeDate,
      const FIX::SecurityExchange& aSecurityExchange,
      const FIX::LatestPx& aLatestPx,
      const FIX::PreSettlementPrice& aPreSettlementPrice,
      const FIX::PreClosePrice& aPreClosePrice,
      const FIX::PreHoldPosition& aPreHoldPosition,
      const FIX::OpenPrice& aOpenPrice,
      const FIX::HighestPrice& aHighestPrice,
      const FIX::LowestPrice& aLowestPrice,
      const FIX::CumQty& aCumQty,
      const FIX::GrossTradeAmt& aGrossTradeAmt,
      const FIX::AvgPx& aAvgPx,
      const FIX::HoldPosition& aHoldPosition,
      const FIX::UpperLimitPrice& aUpperLimitPrice,
      const FIX::LowerLimitPrice& aLowerLimitPrice,
      const FIX::UpdateTime& aUpdateTime,
      const FIX::UpdateMillisec& aUpdateMillisec )
    : Message(MsgType())
    {
      set(aMDReqID);
      set(aSymbol);
      set(aTradeDate);
      set(aSecurityExchange);
      set(aLatestPx);
      set(aPreSettlementPrice);
      set(aPreClosePrice);
      set(aPreHoldPosition);
      set(aOpenPrice);
      set(aHighestPrice);
      set(aLowestPrice);
      set(aCumQty);
      set(aGrossTradeAmt);
      set(aAvgPx);
      set(aHoldPosition);
      set(aUpperLimitPrice);
      set(aLowerLimitPrice);
      set(aUpdateTime);
      set(aUpdateMillisec);
    }

    FIELD_SET(*this, FIX::MDReqID);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::TradeDate);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::LatestPx);
    FIELD_SET(*this, FIX::PreSettlementPrice);
    FIELD_SET(*this, FIX::PreClosePrice);
    FIELD_SET(*this, FIX::PreHoldPosition);
    FIELD_SET(*this, FIX::OpenPrice);
    FIELD_SET(*this, FIX::HighestPrice);
    FIELD_SET(*this, FIX::LowestPrice);
    FIELD_SET(*this, FIX::CumQty);
    FIELD_SET(*this, FIX::GrossTradeAmt);
    FIELD_SET(*this, FIX::AvgPx);
    FIELD_SET(*this, FIX::HoldPosition);
    FIELD_SET(*this, FIX::ClosePrice);
    FIELD_SET(*this, FIX::SettlementPrice);
    FIELD_SET(*this, FIX::UpperLimitPrice);
    FIELD_SET(*this, FIX::LowerLimitPrice);
    FIELD_SET(*this, FIX::BidQty);
    FIELD_SET(*this, FIX::AskQty);
    FIELD_SET(*this, FIX::UpdateTime);
    FIELD_SET(*this, FIX::UpdateMillisec);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::MaturityDay);
    FIELD_SET(*this, FIX::Text);
    FIELD_SET(*this, FIX::NoOfferPriceLevel);
    class NoOfferPriceLevel: public FIX::Group
    {
    public:
    NoOfferPriceLevel() : FIX::Group(8065,133,FIX::message_order(133,135,0)) {}
      FIELD_SET(*this, FIX::OfferPx);
      FIELD_SET(*this, FIX::OfferSize);
    };
    FIELD_SET(*this, FIX::NoBidPriceLevel);
    class NoBidPriceLevel: public FIX::Group
    {
    public:
    NoBidPriceLevel() : FIX::Group(8066,132,FIX::message_order(132,134,0)) {}
      FIELD_SET(*this, FIX::BidPx);
      FIELD_SET(*this, FIX::BidSize);
    };
  };

}

#endif
