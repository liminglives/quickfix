#ifndef FIX42_POSITIONREPORT_H
#define FIX42_POSITIONREPORT_H

#include "Message.h"

namespace FIX42
{

  class PositionReport : public Message
  {
  public:
    PositionReport() : Message(MsgType()) {}
    PositionReport(const FIX::Message& m) : Message(m) {}
    PositionReport(const Message& m) : Message(m) {}
    PositionReport(const PositionReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UPR"); }

    PositionReport(
      const FIX::RequestID& aRequestID,
      const FIX::AvgPx& aAvgPx,
      const FIX::Symbol& aSymbol,
      const FIX::Currency& aCurrency,
      const FIX::SecurityExchange& aSecurityExchange,
      const FIX::LongQty& aLongQty,
      const FIX::ShortQty& aShortQty,
      const FIX::LastRptRequested& aLastRptRequested )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aAvgPx);
      set(aSymbol);
      set(aCurrency);
      set(aSecurityExchange);
      set(aLongQty);
      set(aShortQty);
      set(aLastRptRequested);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::AvgPx);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::LongQty);
    FIELD_SET(*this, FIX::ShortQty);
    FIELD_SET(*this, FIX::LeavesQty);
    FIELD_SET(*this, FIX::LastRptRequested);
    FIELD_SET(*this, FIX::Price);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
