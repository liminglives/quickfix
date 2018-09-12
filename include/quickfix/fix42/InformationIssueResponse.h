#ifndef FIX42_INFORMATIONISSUERESPONSE_H
#define FIX42_INFORMATIONISSUERESPONSE_H

#include "Message.h"

namespace FIX42
{

  class InformationIssueResponse : public Message
  {
  public:
    InformationIssueResponse() : Message(MsgType()) {}
    InformationIssueResponse(const FIX::Message& m) : Message(m) {}
    InformationIssueResponse(const Message& m) : Message(m) {}
    InformationIssueResponse(const InformationIssueResponse& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF032"); }

    InformationIssueResponse(
      const FIX::InformationID& aInformationID )
    : Message(MsgType())
    {
      set(aInformationID);
    }

    FIELD_SET(*this, FIX::InformationID);
  };

}

#endif
