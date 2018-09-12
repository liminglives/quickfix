#ifndef FIX42_BALANCEREPORT_H
#define FIX42_BALANCEREPORT_H

#include "Message.h"

namespace FIX42
{

  class BalanceReport : public Message
  {
  public:
    BalanceReport() : Message(MsgType()) {}
    BalanceReport(const FIX::Message& m) : Message(m) {}
    BalanceReport(const Message& m) : Message(m) {}
    BalanceReport(const BalanceReport& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UBR"); }

    BalanceReport(
      const FIX::RequestID& aRequestID,
      const FIX::Currency& aCurrency,
      const FIX::UseableAmt& aUseableAmt,
      const FIX::LastRptRequested& aLastRptRequested )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aCurrency);
      set(aUseableAmt);
      set(aLastRptRequested);
    }

    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::UseableAmt);
    FIELD_SET(*this, FIX::LastRptRequested);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
