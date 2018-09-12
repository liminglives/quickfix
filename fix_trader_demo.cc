// Author: Zhiwei Xiao (zwxiao@gmail.com)

#define _GLIBCXX_USE_NANOSLEEP

#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <fstream>
#include <stdexcept>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"

#include "quickfix/fix42/UserLogonRequest.h"
#include "quickfix/fix42/UserLogonResponse.h"
#include "quickfix/fix42/NewOrderSingle.h"
#include "quickfix/fix42/ExecutionReport.h"
#include "quickfix/fix42/OrderCancelRequest.h"
#include "quickfix/fix42/OrderCancelReject.h"
#include "quickfix/fix42/RequestForPosition.h"
#include "quickfix/fix42/PositionReport.h"
#include "quickfix/fix42/RequestForBalance.h"
#include "quickfix/fix42/BalanceReport.h"

#include "quickfix/Exceptions.h"
#include "quickfix/FileStore.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/Session.h"

#include "quickfix/SessionSettings.h"
#include "quickfix/FileLog.h"

using namespace std::chrono;

class Application :
      public FIX::Application,
      public FIX::MessageCracker
{
public:
  void run();

private:
  void onCreate( const FIX::SessionID& ) {}
  void onLogon( const FIX::SessionID& sessionID );
  void onLogout( const FIX::SessionID& sessionID );
  void toAdmin( FIX::Message&, const FIX::SessionID& ) {}
  void toApp( FIX::Message&, const FIX::SessionID& )
  throw( FIX::DoNotSend ) override;
  void fromAdmin( const FIX::Message&, const FIX::SessionID& )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {}
  void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
  throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );

  void onMessage( const FIX42::ExecutionReport&, const FIX::SessionID& );
  void onMessage( const FIX42::OrderCancelReject&, const FIX::SessionID& );
  void onMessage( const FIX42::PositionReport&, const FIX::SessionID& );
  void onMessage( const FIX42::BalanceReport&, const FIX::SessionID& );
  void onMessage( const FIX42::UserLogonResponse& msg, const FIX::SessionID& session );


  std::string NextOrderRef();
  FIX42::NewOrderSingle SendNewOrder();
  FIX42::OrderCancelRequest SendCancelRequest(const std::string& ori_order_id);
  void SendPositionRequest();
  void SendBalanceRequest();

private:
  void Test();

  long begin_epoch_secs_;
  std::string begin_epoch_secs_str_;
  int order_ref_;
};

const std::string kFixConfigFile = "./FIX42.xml";
const std::string kOrderRefSuffix = "RT";

void Application::onLogon( const FIX::SessionID& sessionID )
{
  std::cout << std::endl << "Logon - " << sessionID << std::endl;

  FIX42::UserLogonRequest msg(
      FIX::RequestID(begin_epoch_secs_str_),
      FIX::ClientID("RUITIAN"),
      FIX::EncryptMethod(0),
      FIX::LogonPasswd("RUITIAN"));

  msg.getHeader().setField(
      FIX::OnBehalfOfCompID("RUITIAN"));
  msg.getHeader().setField(FIX::SenderCompID("RUITIANUAT"));
  msg.getHeader().setField(FIX::TargetCompID("CICCIMSUAT"));
  FIX::Session::sendToTarget(msg);
}

void Application::onMessage( const FIX42::UserLogonResponse& msg, const FIX::SessionID& session ) {
    std::cout << "onMessage UserLogonResponse" << std::endl;
  Test();
}

void Application::onLogout( const FIX::SessionID& sessionID )
{
  std::cout << std::endl << "Logout - " << sessionID << std::endl;
}

void Application::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType )
{
  crack( message, sessionID );
  std::cout << std::endl << "fromAPP IN: " << message << std::endl;
}

void Application::toApp( FIX::Message& message, const FIX::SessionID& )
throw( FIX::DoNotSend )
{
  try
  {
    FIX::PossDupFlag possDupFlag;
    message.getHeader().getField( possDupFlag );
    if ( possDupFlag ) throw FIX::DoNotSend();
  }
  catch ( FIX::FieldNotFound& ) {}

  std::cout << std::endl << "toApp OUT: " << message << std::endl;
}

void Application::onMessage( const FIX42::ExecutionReport& msg, const FIX::SessionID& ) {
  std::cout << "-- Receive ExecutionReport: " << msg.toXML() << std::endl;
}
void Application::onMessage( const FIX42::OrderCancelReject& msg, const FIX::SessionID& ) {
  std::cout << "-- Receive OrderCancelReject: " << msg.toXML() << std::endl;
}
void Application::onMessage( const FIX42::PositionReport& msg, const FIX::SessionID& ) {
  std::cout << "-- Receive PositionReport: " << msg.toXML() << std::endl;
}
void Application::onMessage( const FIX42::BalanceReport& msg, const FIX::SessionID& ) {
  std::cout << "-- Receive BalanceReport: " << msg.toXML() << std::endl;
}

void Application::run()
{
  std::cout << "init xml " << FIX::Message::InitializeXML(kFixConfigFile) << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(10));
}

void Application::Test() {
  {
    std::cout << "Test" << std::endl;
    auto now = system_clock::now();
    time_t tnow = system_clock::to_time_t(now);
    tm *date = std::localtime(&tnow);
    date->tm_hour = 0;
    date->tm_min = 0;
    date->tm_sec = 0;
    auto midnight = system_clock::from_time_t(std::mktime(date));
    begin_epoch_secs_ = duration_cast<seconds>(now - midnight).count();
    begin_epoch_secs_str_ = std::to_string(begin_epoch_secs_);
  }
  order_ref_ = 1;
  // sleep for 2 seconds for real logon
  //std::this_thread::sleep_for(std::chrono::seconds(2));

  {
    auto order = SendNewOrder();
    FIX::ClOrdID fix_order_id;
    order.get(fix_order_id);
    SendCancelRequest(fix_order_id.getValue());
    // std::this_thread::sleep_for(std::chrono::seconds(5));
  }

  {
    SendPositionRequest();
    SendBalanceRequest();
  }
}

std::string Application::NextOrderRef() {
  char ref[32];
  snprintf(ref, sizeof(ref), "%05ld%07d%s",
           begin_epoch_secs_, order_ref_++, kOrderRefSuffix.c_str());
  return ref;
}

FIX42::NewOrderSingle Application::SendNewOrder()
{
    std::cout << "SendNewOrder" << std::endl;
  FIX42::NewOrderSingle newOrderSingle(
      FIX::ClOrdID(NextOrderRef()),
      FIX::HandlInst(FIX::HandlInst_AUTOMATED_EXECUTION_ORDER_PRIVATE_NO_BROKER_INTERVENTION),
      FIX::Symbol("600000"),
      FIX::Side(FIX::Side_BUY),
      FIX::TransactTime(),
      FIX::OrdType(FIX::OrdType_LIMIT));

  newOrderSingle.set(FIX::SecurityExchange("XSSC")); // XSEC for sz
  newOrderSingle.set(FIX::Currency("CNY"));
  newOrderSingle.set(FIX::OrderQty(1000));
  newOrderSingle.set(FIX::Price(12.53));
  newOrderSingle.set(FIX::Account("RUITIAN"));
  newOrderSingle.set(FIX::TimeInForce(FIX::TimeInForce_DAY));

  newOrderSingle.getHeader().setField(FIX::OnBehalfOfCompID("RUITIAN"));
  newOrderSingle.getHeader().setField(FIX::SenderCompID("RUITIANUAT"));
  newOrderSingle.getHeader().setField(FIX::TargetCompID("CICCIMSUAT"));

  bool res = FIX::Session::sendToTarget(newOrderSingle);

  std::cout << "-- Send new order: " << res << std::endl;

  return newOrderSingle;
}

FIX42::OrderCancelRequest Application::SendCancelRequest(const std::string& ori_order_id)
{
    std::cout << "SendCancelRequest" << std::endl;
  FIX42::OrderCancelRequest orderCancelRequest(
      FIX::OrigClOrdID(ori_order_id),
      FIX::ClOrdID(NextOrderRef()),
      FIX::Symbol("600000"),
      FIX::Side(FIX::Side_BUY),
      FIX::TransactTime());

  orderCancelRequest.set(FIX::Account("RUITIAN"));
  orderCancelRequest.getHeader().setField(FIX::OnBehalfOfCompID("RUITIAN"));
  orderCancelRequest.getHeader().setField(FIX::SenderCompID("RUITIANUAT"));
  orderCancelRequest.getHeader().setField(FIX::TargetCompID("CICCIMSUAT"));

  bool res = FIX::Session::sendToTarget(orderCancelRequest);

  std::cout << "-- Cancel order: " << res << std::endl;

  return orderCancelRequest;
}

void Application::SendPositionRequest() {
    std::cout << "SendPositionRequest" << std::endl;
  try {
    FIX42::RequestForPosition request;
    request.set(FIX::Account("RUITIAN"));
    request.set(FIX::RequestID(begin_epoch_secs_str_));
    request.getHeader().setField(FIX::OnBehalfOfCompID("RUITIAN"));
    request.getHeader().setField(FIX::SenderCompID("RUITIANUAT"));
    request.getHeader().setField(FIX::TargetCompID("CICCIMSUAT"));

    bool res = FIX::Session::sendToTarget(request);
    std::cout << "-- Position request: " << res << std::endl;
  } catch (std::exception &e) {
    std::cerr << "SendPositionRequest Failed: " << e.what() << std::endl;
  }
}

void Application::SendBalanceRequest() {
    std::cout << "SendBalanceRequest" << std::endl;
  try {
    FIX42::RequestForBalance request;
    request.set(FIX::Account("RUITIAN"));
    request.set(FIX::RequestID(begin_epoch_secs_str_));
    request.getHeader().setField(FIX::OnBehalfOfCompID("RUITIAN"));
    request.getHeader().setField(FIX::SenderCompID("RUITIANUAT"));
    request.getHeader().setField(FIX::TargetCompID("CICCIMSUAT"));

    bool res = FIX::Session::sendToTarget(request);
    std::cout << "-- Balance request: " << res << std::endl;
  } catch (std::exception &e) {
    std::cerr << "SendBalanceRequest Failed: " << e.what() << std::endl;
  }
}

int main( int argc, char** argv )
{
  std::string file = "fix.cfg";

  try
  {
    FIX::SessionSettings settings( file );

    Application application;
    FIX::FileStoreFactory storeFactory( settings );
    FIX::FileLogFactory logFactory( settings );
    std::cout << "create" << std::endl;
    logFactory.create();
    std::cout << "end create" << std::endl;
    FIX::SocketInitiator initiator( application, storeFactory, settings, logFactory );

    initiator.start();
    application.run();
    initiator.stop();

    return 0;
  } catch (std::exception & e) {
    std::cerr << e.what();
    return 1;
  }
}
