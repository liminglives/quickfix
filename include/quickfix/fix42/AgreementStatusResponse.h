#ifndef FIX42_AGREEMENTSTATUSRESPONSE_H
#define FIX42_AGREEMENTSTATUSRESPONSE_H

#include "Message.h"

namespace FIX42
{

  class AgreementStatusResponse : public Message
  {
  public:
    AgreementStatusResponse() : Message(MsgType()) {}
    AgreementStatusResponse(const FIX::Message& m) : Message(m) {}
    AgreementStatusResponse(const Message& m) : Message(m) {}
    AgreementStatusResponse(const AgreementStatusResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType(" UF025"); }

    AgreementStatusResponse(
      const FIX::RequestID& aRequestID,
      const FIX::SecurityExchange& aSecurityExchange,
      const FIX::OneLotQty& aOneLotQty,
      const FIX::MaxLotQty& aMaxLotQty,
      const FIX::MaxHoldPosition& aMaxHoldPosition,
      const FIX::VarietyCode& aVarietyCode,
      const FIX::VarietyName& aVarietyName,
      const FIX::MinPxAlterUnit& aMinPxAlterUnit )
    : Message(MsgType())
    {
      set(aRequestID);
      set(aSecurityExchange);
      set(aOneLotQty);
      set(aMaxLotQty);
      set(aMaxHoldPosition);
      set(aVarietyCode);
      set(aVarietyName);
      set(aMinPxAlterUnit);
    }

    FIELD_SET(*this, FIX::RequestID);
    FIELD_SET(*this, FIX::TotalRetNum);
    FIELD_SET(*this, FIX::PresentRetNum);
    FIELD_SET(*this, FIX::NextFlag);
    FIELD_SET(*this, FIX::SecurityExchange);
    FIELD_SET(*this, FIX::ExchangeName);
    FIELD_SET(*this, FIX::Symbol);
    FIELD_SET(*this, FIX::SymbolSfx);
    FIELD_SET(*this, FIX::OneLotQty);
    FIELD_SET(*this, FIX::MaturityMonthYear);
    FIELD_SET(*this, FIX::MaxLotQty);
    FIELD_SET(*this, FIX::MaxHoldPosition);
    FIELD_SET(*this, FIX::VarietyCode);
    FIELD_SET(*this, FIX::VarietyName);
    FIELD_SET(*this, FIX::MinPxAlterUnit);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
