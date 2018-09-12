#ifndef FIX42_POSITIONSTATUSRESPONSE_H
#define FIX42_POSITIONSTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class PositionStatusResponse : public Message
  {
  public:
    PositionStatusResponse() : Message(MsgType()) {}
    PositionStatusResponse(const FIX::Message& m) : Message(m) {}
    PositionStatusResponse(const Message& m) : Message(m) {}
    PositionStatusResponse(const PositionStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF008"); }

    PositionStatusResponse(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::SecurityExchange& aSecurityExchange,
      const FIX::Side& aSide,
      const FIX::HedgeFlag& aHedgeFlag,
      const FIX::CumQty& aCumQty,
      const FIX::TdPosition& aTdPosition,
      const FIX::YDPosition& aYDPosition )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aSecurityExchange);
      set(aSide);
      set(aHedgeFlag);
      set(aCumQty);
      set(aTdPosition);
      set(aYDPosition);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::TotalRetNum);
    FIELD_SET(*this, FIX::PresentRetNum);
    FIELD_SET(*this, FIX::NextFlag);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::LatestPx);
    FIELD_SET(*this, FIX::Side);
    FIELD_SET(*this, FIX::HedgeFlag);
    FIELD_SET(*this, FIX::CumQty);
    FIELD_SET(*this, FIX::TdPosition);
    FIELD_SET(*this, FIX::YDPosition);
    FIELD_SET(*this, FIX::FrozenPosition);
    FIELD_SET(*this, FIX::FrozenAmt);
    FIELD_SET(*this, FIX::PositionDate);
    FIELD_SET(*this, FIX::AvgPx);
    FIELD_SET(*this, FIX::Commission);
    FIELD_SET(*this, FIX::PositionProfit);
    FIELD_SET(*this, FIX::PositionPrice);
    FIELD_SET(*this, FIX::OneLotQty);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
