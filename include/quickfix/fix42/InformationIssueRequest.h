#ifndef FIX42_INFORMATIONISSUEREQUEST_H
#define FIX42_INFORMATIONISSUEREQUEST_H

#include "Message.h"

namespace FIX42
{

  class InformationIssueRequest : public Message
  {
  public:
    InformationIssueRequest() : Message(MsgType()) {}
    InformationIssueRequest(const FIX::Message& m) : Message(m) {}
    InformationIssueRequest(const Message& m) : Message(m) {}
    InformationIssueRequest(const InformationIssueRequest& m) : Message(m) {}
    static FIX::MsgType MsgType() { return FIX::MsgType("UF031"); }

    InformationIssueRequest(
      const FIX::InformationID& aInformationID,
      const FIX::Text& aText )
    : Message(MsgType())
    {
      set(aInformationID);
      set(aText);
    }

    FIELD_SET(*this, FIX::InformationID);
    FIELD_SET(*this, FIX::Text);
  };

}

#endif
