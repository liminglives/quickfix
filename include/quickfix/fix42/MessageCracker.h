/* -*- C++ -*- */
 
/****************************************************************************
** Copyright (c) 2001-2014
**
** This file is part of the QuickFIX FIX Engine
**
** This file may be distributed under the terms of the quickfixengine.org
** license as defined by quickfixengine.org and appearing in the file
** LICENSE included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.quickfixengine.org/LICENSE for licensing information.
**
** Contact ask@quickfixengine.org if any conditions of this licensing are
** not clear to you.
**
****************************************************************************/

#ifndef FIX42_MESSAGECRACKER_H
#define FIX42_MESSAGECRACKER_H


#include "../SessionID.h"
#include "../Exceptions.h"

#include "../fix42/Message.h"

namespace FIX42
{  
  class Heartbeat; 
  class Logon; 
  class TestRequest; 
  class ResendRequest; 
  class Reject; 
  class SequenceReset; 
  class Logout; 
  class Advertisement; 
  class IndicationofInterest; 
  class News; 
  class Email; 
  class QuoteRequest; 
  class Quote; 
  class MassQuote; 
  class QuoteCancel; 
  class QuoteStatusRequest; 
  class QuoteAcknowledgement; 
  class MarketDataRequest; 
  class MarketDataSnapshotFullRefresh; 
  class MarketDataIncrementalRefresh; 
  class MarketDataRequestReject; 
  class SecurityDefinitionRequest; 
  class SecurityDefinition; 
  class SecurityStatusRequest; 
  class SecurityStatus; 
  class TradingSessionStatusRequest; 
  class TradingSessionStatus; 
  class NewOrderSingle; 
  class ExecutionReport; 
  class DontKnowTrade; 
  class OrderCancelReplaceRequest; 
  class OrderCancelRequest; 
  class OrderCancelReject; 
  class OrderStatusRequest; 
  class Allocation; 
  class AllocationACK; 
  class SettlementInstructions; 
  class BidRequest; 
  class BidResponse; 
  class NewOrderList; 
  class ListStrikePrice; 
  class ListStatus; 
  class ListExecute; 
  class ListCancelRequest; 
  class ListStatusRequest; 
  class BusinessMessageReject; 
  class RequestForPosition; 
  class PositionReport; 
  class RequestForBalance; 
  class BalanceReport; 
  class UserLogonRequest; 
  class UserLogonResponse; 
  class UserLogoutRequest; 
  class UserLogoutResponse; 
  class UserChangePassWdRequest; 
  class UserChangePassWdResponse; 
  class PositionStatusRequest; 
  class PositionStatusResponse; 
  class MaxOperationPositionStatusRequest; 
  class MaxOperationPositionStatusResponse; 
  class AllOrdersStatusRequest; 
  class AllOrdersStatusResponse; 
  class SettlementResultStatusRequest; 
  class SettlementResultStatusResponse; 
  class SettlementResultComfirmRequest; 
  class SettlementResultComfirmResponse; 
  class SettlementResultComfirmStatusRequest; 
  class MarginRateStatusRequest; 
  class MarginRateStatusResponse; 
  class CommissionRateStatusRequest; 
  class CommissionRateStatusResponse; 
  class CustomerCapitalStatusRequest; 
  class CustomerCapitalStatusResponse; 
  class AgreementStatusRequest; 
  class AgreementStatusResponse; 
  class MarketDataStatusRequest; 
  class MarketDataStatusResponse; 
  class MarketDataStatusCancelRequest; 
  class MarketDataStatusCancelResponse; 
  class ResponseGapFillResendRequest; 
  class InformationIssueRequest; 
  class InformationIssueResponse; 
  class RequestErrorInformation;

  class MessageCracker
  {
  public:
  virtual ~MessageCracker() {}
  virtual void onMessage( const Message&, const FIX::SessionID& )
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( Message&, const FIX::SessionID& )
    { throw FIX::UnsupportedMessageType(); }
 virtual void onMessage( const Heartbeat&, const FIX::SessionID& ) 
    {}
  virtual void onMessage( const Logon&, const FIX::SessionID& ) 
    {}
  virtual void onMessage( const TestRequest&, const FIX::SessionID& ) 
    {}
  virtual void onMessage( const ResendRequest&, const FIX::SessionID& ) 
    {}
  virtual void onMessage( const Reject&, const FIX::SessionID& ) 
    {}
  virtual void onMessage( const SequenceReset&, const FIX::SessionID& ) 
    {}
  virtual void onMessage( const Logout&, const FIX::SessionID& ) 
    {}
  virtual void onMessage( const Advertisement&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const IndicationofInterest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const News&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const Email&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const QuoteRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const Quote&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MassQuote&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const QuoteCancel&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const QuoteStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const QuoteAcknowledgement&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarketDataRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarketDataSnapshotFullRefresh&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarketDataIncrementalRefresh&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarketDataRequestReject&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SecurityDefinitionRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SecurityDefinition&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SecurityStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SecurityStatus&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const TradingSessionStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const TradingSessionStatus&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const NewOrderSingle&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const ExecutionReport&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const DontKnowTrade&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const OrderCancelReplaceRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const OrderCancelRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const OrderCancelReject&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const OrderStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const Allocation&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const AllocationACK&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SettlementInstructions&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const BidRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const BidResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const NewOrderList&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const ListStrikePrice&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const ListStatus&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const ListExecute&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const ListCancelRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const ListStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const BusinessMessageReject&, const FIX::SessionID& ) 
    {}
  virtual void onMessage( const RequestForPosition&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const PositionReport&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const RequestForBalance&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const BalanceReport&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const UserLogonRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const UserLogonResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const UserLogoutRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const UserLogoutResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const UserChangePassWdRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const UserChangePassWdResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const PositionStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const PositionStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MaxOperationPositionStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MaxOperationPositionStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const AllOrdersStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const AllOrdersStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SettlementResultStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SettlementResultStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SettlementResultComfirmRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SettlementResultComfirmResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const SettlementResultComfirmStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarginRateStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarginRateStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const CommissionRateStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const CommissionRateStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const CustomerCapitalStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const CustomerCapitalStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const AgreementStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const AgreementStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarketDataStatusRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarketDataStatusResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarketDataStatusCancelRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const MarketDataStatusCancelResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const ResponseGapFillResendRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const InformationIssueRequest&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const InformationIssueResponse&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( const RequestErrorInformation&, const FIX::SessionID& ) 
    { throw FIX::UnsupportedMessageType(); }
  virtual void onMessage( Heartbeat&, const FIX::SessionID& ) {} 
 virtual void onMessage( Logon&, const FIX::SessionID& ) {} 
 virtual void onMessage( TestRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( ResendRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( Reject&, const FIX::SessionID& ) {} 
 virtual void onMessage( SequenceReset&, const FIX::SessionID& ) {} 
 virtual void onMessage( Logout&, const FIX::SessionID& ) {} 
 virtual void onMessage( Advertisement&, const FIX::SessionID& ) {} 
 virtual void onMessage( IndicationofInterest&, const FIX::SessionID& ) {} 
 virtual void onMessage( News&, const FIX::SessionID& ) {} 
 virtual void onMessage( Email&, const FIX::SessionID& ) {} 
 virtual void onMessage( QuoteRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( Quote&, const FIX::SessionID& ) {} 
 virtual void onMessage( MassQuote&, const FIX::SessionID& ) {} 
 virtual void onMessage( QuoteCancel&, const FIX::SessionID& ) {} 
 virtual void onMessage( QuoteStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( QuoteAcknowledgement&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarketDataRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarketDataSnapshotFullRefresh&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarketDataIncrementalRefresh&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarketDataRequestReject&, const FIX::SessionID& ) {} 
 virtual void onMessage( SecurityDefinitionRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( SecurityDefinition&, const FIX::SessionID& ) {} 
 virtual void onMessage( SecurityStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( SecurityStatus&, const FIX::SessionID& ) {} 
 virtual void onMessage( TradingSessionStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( TradingSessionStatus&, const FIX::SessionID& ) {} 
 virtual void onMessage( NewOrderSingle&, const FIX::SessionID& ) {} 
 virtual void onMessage( ExecutionReport&, const FIX::SessionID& ) {} 
 virtual void onMessage( DontKnowTrade&, const FIX::SessionID& ) {} 
 virtual void onMessage( OrderCancelReplaceRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( OrderCancelRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( OrderCancelReject&, const FIX::SessionID& ) {} 
 virtual void onMessage( OrderStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( Allocation&, const FIX::SessionID& ) {} 
 virtual void onMessage( AllocationACK&, const FIX::SessionID& ) {} 
 virtual void onMessage( SettlementInstructions&, const FIX::SessionID& ) {} 
 virtual void onMessage( BidRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( BidResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( NewOrderList&, const FIX::SessionID& ) {} 
 virtual void onMessage( ListStrikePrice&, const FIX::SessionID& ) {} 
 virtual void onMessage( ListStatus&, const FIX::SessionID& ) {} 
 virtual void onMessage( ListExecute&, const FIX::SessionID& ) {} 
 virtual void onMessage( ListCancelRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( ListStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( BusinessMessageReject&, const FIX::SessionID& ) {} 
 virtual void onMessage( RequestForPosition&, const FIX::SessionID& ) {} 
 virtual void onMessage( PositionReport&, const FIX::SessionID& ) {} 
 virtual void onMessage( RequestForBalance&, const FIX::SessionID& ) {} 
 virtual void onMessage( BalanceReport&, const FIX::SessionID& ) {} 
 virtual void onMessage( UserLogonRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( UserLogonResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( UserLogoutRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( UserLogoutResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( UserChangePassWdRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( UserChangePassWdResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( PositionStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( PositionStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( MaxOperationPositionStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( MaxOperationPositionStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( AllOrdersStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( AllOrdersStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( SettlementResultStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( SettlementResultStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( SettlementResultComfirmRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( SettlementResultComfirmResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( SettlementResultComfirmStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarginRateStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarginRateStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( CommissionRateStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( CommissionRateStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( CustomerCapitalStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( CustomerCapitalStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( AgreementStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( AgreementStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarketDataStatusRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarketDataStatusResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarketDataStatusCancelRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( MarketDataStatusCancelResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( ResponseGapFillResendRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( InformationIssueRequest&, const FIX::SessionID& ) {} 
 virtual void onMessage( InformationIssueResponse&, const FIX::SessionID& ) {} 
 virtual void onMessage( RequestErrorInformation&, const FIX::SessionID& ) {} 

public:
  void crack( const Message& message, 
              const FIX::SessionID& sessionID )
  {
    const std::string& msgTypeValue 
      = message.getHeader().getField( FIX::FIELD::MsgType );
    
    if( msgTypeValue == "0" )
      onMessage( (const Heartbeat&)message, sessionID );
    else
    if( msgTypeValue == "A" )
      onMessage( (const Logon&)message, sessionID );
    else
    if( msgTypeValue == "1" )
      onMessage( (const TestRequest&)message, sessionID );
    else
    if( msgTypeValue == "2" )
      onMessage( (const ResendRequest&)message, sessionID );
    else
    if( msgTypeValue == "3" )
      onMessage( (const Reject&)message, sessionID );
    else
    if( msgTypeValue == "4" )
      onMessage( (const SequenceReset&)message, sessionID );
    else
    if( msgTypeValue == "5" )
      onMessage( (const Logout&)message, sessionID );
    else
    if( msgTypeValue == "7" )
      onMessage( (const Advertisement&)message, sessionID );
    else
    if( msgTypeValue == "6" )
      onMessage( (const IndicationofInterest&)message, sessionID );
    else
    if( msgTypeValue == "B" )
      onMessage( (const News&)message, sessionID );
    else
    if( msgTypeValue == "C" )
      onMessage( (const Email&)message, sessionID );
    else
    if( msgTypeValue == "R" )
      onMessage( (const QuoteRequest&)message, sessionID );
    else
    if( msgTypeValue == "S" )
      onMessage( (const Quote&)message, sessionID );
    else
    if( msgTypeValue == "i" )
      onMessage( (const MassQuote&)message, sessionID );
    else
    if( msgTypeValue == "Z" )
      onMessage( (const QuoteCancel&)message, sessionID );
    else
    if( msgTypeValue == "a" )
      onMessage( (const QuoteStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "b" )
      onMessage( (const QuoteAcknowledgement&)message, sessionID );
    else
    if( msgTypeValue == "V" )
      onMessage( (const MarketDataRequest&)message, sessionID );
    else
    if( msgTypeValue == "W" )
      onMessage( (const MarketDataSnapshotFullRefresh&)message, sessionID );
    else
    if( msgTypeValue == "X" )
      onMessage( (const MarketDataIncrementalRefresh&)message, sessionID );
    else
    if( msgTypeValue == "Y" )
      onMessage( (const MarketDataRequestReject&)message, sessionID );
    else
    if( msgTypeValue == "c" )
      onMessage( (const SecurityDefinitionRequest&)message, sessionID );
    else
    if( msgTypeValue == "d" )
      onMessage( (const SecurityDefinition&)message, sessionID );
    else
    if( msgTypeValue == "e" )
      onMessage( (const SecurityStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "f" )
      onMessage( (const SecurityStatus&)message, sessionID );
    else
    if( msgTypeValue == "g" )
      onMessage( (const TradingSessionStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "h" )
      onMessage( (const TradingSessionStatus&)message, sessionID );
    else
    if( msgTypeValue == "D" )
      onMessage( (const NewOrderSingle&)message, sessionID );
    else
    if( msgTypeValue == "8" )
      onMessage( (const ExecutionReport&)message, sessionID );
    else
    if( msgTypeValue == "Q" )
      onMessage( (const DontKnowTrade&)message, sessionID );
    else
    if( msgTypeValue == "G" )
      onMessage( (const OrderCancelReplaceRequest&)message, sessionID );
    else
    if( msgTypeValue == "F" )
      onMessage( (const OrderCancelRequest&)message, sessionID );
    else
    if( msgTypeValue == "9" )
      onMessage( (const OrderCancelReject&)message, sessionID );
    else
    if( msgTypeValue == "H" )
      onMessage( (const OrderStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "J" )
      onMessage( (const Allocation&)message, sessionID );
    else
    if( msgTypeValue == "P" )
      onMessage( (const AllocationACK&)message, sessionID );
    else
    if( msgTypeValue == "T" )
      onMessage( (const SettlementInstructions&)message, sessionID );
    else
    if( msgTypeValue == "k" )
      onMessage( (const BidRequest&)message, sessionID );
    else
    if( msgTypeValue == "l" )
      onMessage( (const BidResponse&)message, sessionID );
    else
    if( msgTypeValue == "E" )
      onMessage( (const NewOrderList&)message, sessionID );
    else
    if( msgTypeValue == "m" )
      onMessage( (const ListStrikePrice&)message, sessionID );
    else
    if( msgTypeValue == "N" )
      onMessage( (const ListStatus&)message, sessionID );
    else
    if( msgTypeValue == "L" )
      onMessage( (const ListExecute&)message, sessionID );
    else
    if( msgTypeValue == "K" )
      onMessage( (const ListCancelRequest&)message, sessionID );
    else
    if( msgTypeValue == "M" )
      onMessage( (const ListStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "j" )
      onMessage( (const BusinessMessageReject&)message, sessionID );
    else
    if( msgTypeValue == "URP" )
      onMessage( (const RequestForPosition&)message, sessionID );
    else
    if( msgTypeValue == "UPR" )
      onMessage( (const PositionReport&)message, sessionID );
    else
    if( msgTypeValue == "URB" )
      onMessage( (const RequestForBalance&)message, sessionID );
    else
    if( msgTypeValue == "UBR" )
      onMessage( (const BalanceReport&)message, sessionID );
    else
    if( msgTypeValue == "UF001" )
      onMessage( (const UserLogonRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF002" )
      onMessage( (const UserLogonResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF003" )
      onMessage( (const UserLogoutRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF004" )
      onMessage( (const UserLogoutResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF005" )
      onMessage( (const UserChangePassWdRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF006" )
      onMessage( (const UserChangePassWdResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF007" )
      onMessage( (const PositionStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF008" )
      onMessage( (const PositionStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF009" )
      onMessage( (const MaxOperationPositionStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF010" )
      onMessage( (const MaxOperationPositionStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF011" )
      onMessage( (const AllOrdersStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF012" )
      onMessage( (const AllOrdersStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF013" )
      onMessage( (const SettlementResultStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF014" )
      onMessage( (const SettlementResultStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF015" )
      onMessage( (const SettlementResultComfirmRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF016" )
      onMessage( (const SettlementResultComfirmResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF017" )
      onMessage( (const SettlementResultComfirmStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF018" )
      onMessage( (const MarginRateStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF019" )
      onMessage( (const MarginRateStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF020" )
      onMessage( (const CommissionRateStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF021" )
      onMessage( (const CommissionRateStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF022" )
      onMessage( (const CustomerCapitalStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF023" )
      onMessage( (const CustomerCapitalStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == " UF024" )
      onMessage( (const AgreementStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == " UF025" )
      onMessage( (const AgreementStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF026" )
      onMessage( (const MarketDataStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF027" )
      onMessage( (const MarketDataStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF028" )
      onMessage( (const MarketDataStatusCancelRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF029" )
      onMessage( (const MarketDataStatusCancelResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF030" )
      onMessage( (const ResponseGapFillResendRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF031" )
      onMessage( (const InformationIssueRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF032" )
      onMessage( (const InformationIssueResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF033" )
      onMessage( (const RequestErrorInformation&)message, sessionID );
    else onMessage( message, sessionID );
  }
  
void crack( Message& message, 
            const FIX::SessionID& sessionID )
  {
    FIX::MsgType msgType;
    message.getHeader().getField(msgType);
    std::string msgTypeValue = msgType.getValue();
    
    if( msgTypeValue == "0" )
      onMessage( (Heartbeat&)message, sessionID );
    else
    if( msgTypeValue == "A" )
      onMessage( (Logon&)message, sessionID );
    else
    if( msgTypeValue == "1" )
      onMessage( (TestRequest&)message, sessionID );
    else
    if( msgTypeValue == "2" )
      onMessage( (ResendRequest&)message, sessionID );
    else
    if( msgTypeValue == "3" )
      onMessage( (Reject&)message, sessionID );
    else
    if( msgTypeValue == "4" )
      onMessage( (SequenceReset&)message, sessionID );
    else
    if( msgTypeValue == "5" )
      onMessage( (Logout&)message, sessionID );
    else
    if( msgTypeValue == "7" )
      onMessage( (Advertisement&)message, sessionID );
    else
    if( msgTypeValue == "6" )
      onMessage( (IndicationofInterest&)message, sessionID );
    else
    if( msgTypeValue == "B" )
      onMessage( (News&)message, sessionID );
    else
    if( msgTypeValue == "C" )
      onMessage( (Email&)message, sessionID );
    else
    if( msgTypeValue == "R" )
      onMessage( (QuoteRequest&)message, sessionID );
    else
    if( msgTypeValue == "S" )
      onMessage( (Quote&)message, sessionID );
    else
    if( msgTypeValue == "i" )
      onMessage( (MassQuote&)message, sessionID );
    else
    if( msgTypeValue == "Z" )
      onMessage( (QuoteCancel&)message, sessionID );
    else
    if( msgTypeValue == "a" )
      onMessage( (QuoteStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "b" )
      onMessage( (QuoteAcknowledgement&)message, sessionID );
    else
    if( msgTypeValue == "V" )
      onMessage( (MarketDataRequest&)message, sessionID );
    else
    if( msgTypeValue == "W" )
      onMessage( (MarketDataSnapshotFullRefresh&)message, sessionID );
    else
    if( msgTypeValue == "X" )
      onMessage( (MarketDataIncrementalRefresh&)message, sessionID );
    else
    if( msgTypeValue == "Y" )
      onMessage( (MarketDataRequestReject&)message, sessionID );
    else
    if( msgTypeValue == "c" )
      onMessage( (SecurityDefinitionRequest&)message, sessionID );
    else
    if( msgTypeValue == "d" )
      onMessage( (SecurityDefinition&)message, sessionID );
    else
    if( msgTypeValue == "e" )
      onMessage( (SecurityStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "f" )
      onMessage( (SecurityStatus&)message, sessionID );
    else
    if( msgTypeValue == "g" )
      onMessage( (TradingSessionStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "h" )
      onMessage( (TradingSessionStatus&)message, sessionID );
    else
    if( msgTypeValue == "D" )
      onMessage( (NewOrderSingle&)message, sessionID );
    else
    if( msgTypeValue == "8" )
      onMessage( (ExecutionReport&)message, sessionID );
    else
    if( msgTypeValue == "Q" )
      onMessage( (DontKnowTrade&)message, sessionID );
    else
    if( msgTypeValue == "G" )
      onMessage( (OrderCancelReplaceRequest&)message, sessionID );
    else
    if( msgTypeValue == "F" )
      onMessage( (OrderCancelRequest&)message, sessionID );
    else
    if( msgTypeValue == "9" )
      onMessage( (OrderCancelReject&)message, sessionID );
    else
    if( msgTypeValue == "H" )
      onMessage( (OrderStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "J" )
      onMessage( (Allocation&)message, sessionID );
    else
    if( msgTypeValue == "P" )
      onMessage( (AllocationACK&)message, sessionID );
    else
    if( msgTypeValue == "T" )
      onMessage( (SettlementInstructions&)message, sessionID );
    else
    if( msgTypeValue == "k" )
      onMessage( (BidRequest&)message, sessionID );
    else
    if( msgTypeValue == "l" )
      onMessage( (BidResponse&)message, sessionID );
    else
    if( msgTypeValue == "E" )
      onMessage( (NewOrderList&)message, sessionID );
    else
    if( msgTypeValue == "m" )
      onMessage( (ListStrikePrice&)message, sessionID );
    else
    if( msgTypeValue == "N" )
      onMessage( (ListStatus&)message, sessionID );
    else
    if( msgTypeValue == "L" )
      onMessage( (ListExecute&)message, sessionID );
    else
    if( msgTypeValue == "K" )
      onMessage( (ListCancelRequest&)message, sessionID );
    else
    if( msgTypeValue == "M" )
      onMessage( (ListStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "j" )
      onMessage( (BusinessMessageReject&)message, sessionID );
    else
    if( msgTypeValue == "URP" )
      onMessage( (RequestForPosition&)message, sessionID );
    else
    if( msgTypeValue == "UPR" )
      onMessage( (PositionReport&)message, sessionID );
    else
    if( msgTypeValue == "URB" )
      onMessage( (RequestForBalance&)message, sessionID );
    else
    if( msgTypeValue == "UBR" )
      onMessage( (BalanceReport&)message, sessionID );
    else
    if( msgTypeValue == "UF001" )
      onMessage( (UserLogonRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF002" )
      onMessage( (UserLogonResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF003" )
      onMessage( (UserLogoutRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF004" )
      onMessage( (UserLogoutResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF005" )
      onMessage( (UserChangePassWdRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF006" )
      onMessage( (UserChangePassWdResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF007" )
      onMessage( (PositionStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF008" )
      onMessage( (PositionStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF009" )
      onMessage( (MaxOperationPositionStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF010" )
      onMessage( (MaxOperationPositionStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF011" )
      onMessage( (AllOrdersStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF012" )
      onMessage( (AllOrdersStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF013" )
      onMessage( (SettlementResultStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF014" )
      onMessage( (SettlementResultStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF015" )
      onMessage( (SettlementResultComfirmRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF016" )
      onMessage( (SettlementResultComfirmResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF017" )
      onMessage( (SettlementResultComfirmStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF018" )
      onMessage( (MarginRateStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF019" )
      onMessage( (MarginRateStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF020" )
      onMessage( (CommissionRateStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF021" )
      onMessage( (CommissionRateStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF022" )
      onMessage( (CustomerCapitalStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF023" )
      onMessage( (CustomerCapitalStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == " UF024" )
      onMessage( (AgreementStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == " UF025" )
      onMessage( (AgreementStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF026" )
      onMessage( (MarketDataStatusRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF027" )
      onMessage( (MarketDataStatusResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF028" )
      onMessage( (MarketDataStatusCancelRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF029" )
      onMessage( (MarketDataStatusCancelResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF030" )
      onMessage( (ResponseGapFillResendRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF031" )
      onMessage( (InformationIssueRequest&)message, sessionID );
    else
    if( msgTypeValue == "UF032" )
      onMessage( (InformationIssueResponse&)message, sessionID );
    else
    if( msgTypeValue == "UF033" )
      onMessage( (RequestErrorInformation&)message, sessionID );
    else onMessage( message, sessionID );
  }

  };
}

#endif
