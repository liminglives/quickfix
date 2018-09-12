#ifndef FIX42_ALLORDERSSTATUSRESPONSE_H
#define FIX42_ALLORDERSSTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class AllOrdersStatusResponse : public Message
  {
  public:
    AllOrdersStatusResponse() : Message(MsgType()) {}
    AllOrdersStatusResponse(const FIX::Message& m) : Message(m) {}
    AllOrdersStatusResponse(const Message& m) : Message(m) {}
    AllOrdersStatusResponse(const AllOrdersStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF012"); }

    AllOrdersStatusResponse(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::Account& aAccount,
      const FIX::SecurityExchange& aSecurityExchange,
      const FIX::ClOrdID& aClOrdID,
      const FIX::OrdStatus& aOrdStatus,
      const FIX::OpenClose& aOpenClose,
      const FIX::Side& aSide,
      const FIX::OrderQty& aOrderQty,
      const FIX::OrdType& aOrdType,
      const FIX::LeavesQty& aLeavesQty,
      const FIX::CumQty& aCumQty,
      const FIX::AvgPx& aAvgPx )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aAccount);
      set(aSecurityExchange);
      set(aClOrdID);
      set(aOrdStatus);
      set(aOpenClose);
      set(aSide);
      set(aOrderQty);
      set(aOrdType);
      set(aLeavesQty);
      set(aCumQty);
      set(aAvgPx);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::TotalRetNum);
    FIELD_SET(*this, FIX::PresentRetNum);
    FIELD_SET(*this, FIX::NextFlag);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::Account);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::ClOrdID);
    FIELD_SET(*this, FIX::OrdStatus);
    FIELD_SET(*this, FIX::OpenClose);
    FIELD_SET(*this, FIX::Side);
    FIELD_SET(*this, FIX::OrderQty);
    FIELD_SET(*this, FIX::OrdType);
    FIELD_SET(*this, FIX::Price);
    FIELD_SET(*this, FIX::StopPx);
    FIELD_SET(*this, FIX::TimeInForce);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::LeavesQty);
    FIELD_SET(*this, FIX::CumQty);
    FIELD_SET(*this, FIX::AvgPx);
    FIELD_SET(*this, FIX::TransactTime);
    FIELD_SET(*this, FIX::GrossTradeAmt);
    FIELD_SET(*this, FIX::MinQty);
    FIELD_SET(*this, FIX::OrderEntryTime);
  };

}

#endif
