#ifndef FIX42_CUSTOMERCAPITALSTATUSRESPONSE_H
#define FIX42_CUSTOMERCAPITALSTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class CustomerCapitalStatusResponse : public Message
  {
  public:
    CustomerCapitalStatusResponse() : Message(MsgType()) {}
    CustomerCapitalStatusResponse(const FIX::Message& m) : Message(m) {}
    CustomerCapitalStatusResponse(const Message& m) : Message(m) {}
    CustomerCapitalStatusResponse(const CustomerCapitalStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF023"); }

    CustomerCapitalStatusResponse(
      const FIX::RequestID& aRequestID,
      const FIX::ClientID& aClientID,
      const FIX::BuyMarginAmt& aBuyMarginAmt,
      const FIX::SellMarginAmt& aSellMarginAmt,
      const FIX::SupplementalMarginAmt& aSupplementalMarginAmt,
      const FIX::OccupyMarginAmt& aOccupyMarginAmt,
      const FIX::TotalMarginAmt& aTotalMarginAmt,
      const FIX::YesterdayStlAmt& aYesterdayStlAmt,
      const FIX::BuyFrozenAmt& aBuyFrozenAmt,
      const FIX::SellFrozenAmt& aSellFrozenAmt,
      const FIX::UseableAmt& aUseableAmt,
      const FIX::RiskLevel& aRiskLevel,
      const FIX::ClientSecuType& aClientSecuType,
      const FIX::Riskratio& aRiskratio )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aClientID);
      set(aBuyMarginAmt);
      set(aSellMarginAmt);
      set(aSupplementalMarginAmt);
      set(aOccupyMarginAmt);
      set(aTotalMarginAmt);
      set(aYesterdayStlAmt);
      set(aBuyFrozenAmt);
      set(aSellFrozenAmt);
      set(aUseableAmt);
      set(aRiskLevel);
      set(aClientSecuType);
      set(aRiskratio);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::ClientID);
    FIELD_SET(*this, FIX::BuyMarginAmt);
    FIELD_SET(*this, FIX::SellMarginAmt);
    FIELD_SET(*this, FIX::SupplementalMarginAmt);
    FIELD_SET(*this, FIX::OccupyMarginAmt);
    FIELD_SET(*this, FIX::TotalMarginAmt);
    FIELD_SET(*this, FIX::TotalExMarginAmt);
    FIELD_SET(*this, FIX::YesterdayStlAmt);
    FIELD_SET(*this, FIX::BuyFrozenAmt);
    FIELD_SET(*this, FIX::SellFrozenAmt);
    FIELD_SET(*this, FIX::FrozenCommision);
    FIELD_SET(*this, FIX::TotalFrozenAmt);
    FIELD_SET(*this, FIX::UseableAmt);
    FIELD_SET(*this, FIX::FetchAmt);
    FIELD_SET(*this, FIX::Commission);
    FIELD_SET(*this, FIX::FloatProfit);
    FIELD_SET(*this, FIX::CloseProfit);
    FIELD_SET(*this, FIX::DayFolatProfit);
    FIELD_SET(*this, FIX::DayPaymentAmt);
    FIELD_SET(*this, FIX::DayIncomeAmt);
    FIELD_SET(*this, FIX::RiskLevel);
    FIELD_SET(*this, FIX::ClientSecuType);
    FIELD_SET(*this, FIX::Riskratio);
    FIELD_SET(*this, FIX::Currency);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
