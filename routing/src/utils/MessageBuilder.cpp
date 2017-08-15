#pragma once
#include "data_structures/Message.h"
#include "utils/MessageBuilderProto.pb.h"
#include "utils/MessageBuilder.h"
#include "data_structures/NodeInfo.h"

namespace m2 {
namespace routing {

MessageBuilder::MessageBuilder()
{
}


MessageBuilder::~MessageBuilder()
{
}

std::unique_ptr<Message> MessageBuilder::deserialize(std::vector<char> &buffer)
{
  MessageBuilderProto::Message message;
  std::string buffer_string(buffer.begin(), buffer.end());
  message.ParseFromString(buffer_string);
  NodeInfo node_info{boost::uuids::string_generator()(message.node_info().guid()), message.node_info().ip(), message.node_info().port()};
  boost::uuids::uuid request_id = boost::uuids::string_generator()(message.request_id());
  if (message.message_type() == MessageBuilderProto::PingRequest) {
    return new PingRequestMessage(node_info, request_id);
  } else if (message.message_type() == MessageBuilderProto::StoreRequest){
    UserInfo user_info{
        boost::uuids::string_generator()(message.store_request_message().user_info().guid()),
        message.store_request_message().user_info().domain(),
    };
    return new StoreRequestMessage(node_info, request_id, user_info);
  } else if (message.message_type() == MessageBuilderProto::FindNodeRequest){
    return new FindNodeRequestMessage(node_info, request_id, boost::uuids::string_generator()(message.find_node_request_message().guid()));
  } else if (message.message_type() == MessageBuilderProto::FindDataRequest) {
    return new FindDataRequestMessage(node_info, request_id, boost::uuids::string_generator()(message.find_data_request_message().guid()));
  } else if (message.message_type() == MessageBuilderProto::PingResponse) {
    return new PingResponseMessage(node_info, request_id);
  } else if (message.message_type() == MessageBuilderProto::StoreResponse) {
    return new StoreResponseMessage(node_info, request_id);
  } else if (message.message_type() == MessageBuilderProto::FindNodeResponse) {
    std::list<NodeInfo> nodes_info;
    for (int i = 0; i < message.find_node_response_message().nodes_info_size(); ++i) {
      auto node_info_proto = message.find_node_response_message().nodes_info(i);
      nodes_info.push_back(NodeInfo{boost::uuids::string_generator()(node_info_proto.guid()), node_info_proto.ip(), node_info_proto.port()});
    }
    return new FindNodeResponseMessage(node_info, request_id, nodes_info);
  } else if (message.message_type() == MessageBuilderProto::FindDataResponse) {
    std::list<NodeInfo> nodes_info;
    for (int i = 0; i < message.find_data_response_message().nodes_info_size(); ++i) {
      auto node_info_proto = message.find_data_response_message().nodes_info(i);
      nodes_info.push_back(NodeInfo{boost::uuids::string_generator()(node_info_proto.guid()), node_info_proto.ip(), node_info_proto.port()});
    }
    UserInfo user_info{
        boost::uuids::string_generator()(message.find_data_response_message().user_info().guid()),
        message.find_data_response_message().user_info().domain(),
    };
    return new FindDataResponseMessage(node_info, request_id, user_info, nodes_info);
  } else {
    throw std::runtime_error("Unexpected message type");
  }
}

static std::vector<char> MessageBuilder::serialize(const PingRequestMessage &message)
{
  MessageBuilderProto::Message proto_message;

  proto_message.set_message_type(MessageBuilderProto::PingRequest);
  proto_message.set_request_id(boost::lexical_cast<std::string>(message.request_id));

  auto node_info = proto_message.mutable_node_info();
  node_info->set_guid(boost::lexical_cast<std::string>(message.node_info.guid));
  node_info->set_ip(message.node_info.ip);
  node_info->set_port(message.node_info.port);

  std::string result;
  proto_message.SerializeToString(&result);

  return {result.begin(), result.end()};
}

static std::vector<char> MessageBuilder::serialize(const StoreRequestMessage &message)
{
  MessageBuilderProto::Message proto_message;
  proto_message.set_message_type(MessageBuilderProto::StoreRequest);
  proto_message.set_request_id(boost::lexical_cast<std::string>(message.request_id));

  auto node_info = proto_message.mutable_node_info();
  node_info->set_guid(boost::lexical_cast<std::string>(message.node_info.guid));
  node_info->set_ip(message.node_info.ip);
  node_info->set_port(message.node_info.port);

  auto store_request_message = proto_message.mutable_store_request_message();
  store_request_message->mutable_user_info()->set_guid(boost::lexical_cast<std::string>(message.user_info.guid));
  store_request_message->mutable_user_info()->set_domain(message.user_info.domain);

  std::string result;
  proto_message.SerializeToString(&result);

  return {result.begin(), result.end()};
}

static std::vector<char> MessageBuilder::serialize(const FindNodeRequestMessage &message)
{
  MessageBuilderProto::Message proto_message;
  proto_message.set_message_type(MessageBuilderProto::FindNodeRequest);
  proto_message.set_request_id(boost::lexical_cast<std::string>(message.request_id));

  auto node_info = proto_message.mutable_node_info();
  node_info->set_guid(boost::lexical_cast<std::string>(message.node_info.guid));
  node_info->set_ip(message.node_info.ip);
  node_info->set_port(message.node_info.port);

  auto find_node_request_message = proto_message.mutable_find_node_request_message();
  find_node_request_message->set_guid(boost::lexical_cast<std::string>(message.guid));

  std::string result;
  proto_message.SerializeToString(&result);

  return {result.begin(), result.end()};
}

static std::vector<char> MessageBuilder::serialize(const FindDataRequestMessage &message)
{
  MessageBuilderProto::Message proto_message;
  proto_message.set_message_type(MessageBuilderProto::FindDataRequest);
  proto_message.set_request_id(boost::lexical_cast<std::string>(message.request_id));

  auto node_info = proto_message.mutable_node_info();
  node_info->set_guid(boost::lexical_cast<std::string>(message.node_info.guid));
  node_info->set_ip(message.node_info.ip);
  node_info->set_port(message.node_info.port);

  auto find_data_request_message = proto_message.mutable_find_data_request_message();
  find_data_request_message->set_guid(boost::lexical_cast<std::string>(message.guid));

  std::string result;
  proto_message.SerializeToString(&result);

  return {result.begin(), result.end()};
}

static std::vector<char> MessageBuilder::serialize(const PingResponseMessage &message)
{
  MessageBuilderProto::Message proto_message;
  proto_message.set_message_type(MessageBuilderProto::PingResponse);
  proto_message.set_request_id(boost::lexical_cast<std::string>(message.request_id));

  auto node_info = proto_message.mutable_node_info();
  node_info->set_guid(boost::lexical_cast<std::string>(message.node_info.guid));
  node_info->set_ip(message.node_info.ip);
  node_info->set_port(message.node_info.port);

  std::string result;
  proto_message.SerializeToString(&result);

  return {result.begin(), result.end()};
}


static std::vector<char> MessageBuilder::serialize(const StoreResponseMessage &message)
{
  MessageBuilderProto::Message proto_message;
  proto_message.set_message_type(MessageBuilderProto::StoreResponse);
  proto_message.set_request_id(boost::lexical_cast<std::string>(message.request_id));

  auto node_info = proto_message.mutable_node_info();
  node_info->set_guid(boost::lexical_cast<std::string>(message.node_info.guid));
  node_info->set_ip(message.node_info.ip);
  node_info->set_port(message.node_info.port);

  std::string result;
  proto_message.SerializeToString(&result);

  return {result.begin(), result.end()};
}

static std::vector<char> MessageBuilder::serialize(const FindNodeResponseMessage &message)
{
  MessageBuilderProto::Message proto_message;
  proto_message.set_message_type(MessageBuilderProto::FindNodeResponse);
  proto_message.set_request_id(boost::lexical_cast<std::string>(message.request_id));

  auto node_info = proto_message.mutable_node_info();
  node_info->set_guid(boost::lexical_cast<std::string>(message.node_info.guid));
  node_info->set_ip(message.node_info.ip);
  node_info->set_port(message.node_info.port);

  auto find_node_response_message = proto_message.mutable_find_node_response_message();
  for (auto const& n : message.nodes_info) {
    auto new_node_info = find_node_response_message->add_nodes_info();
    new_node_info->set_guid(boost::lexical_cast<std::string>(n.guid));
    new_node_info->set_ip(n.ip);
    new_node_info->set_port(n.port);
  }

  std::string result;
  proto_message.SerializeToString(&result);

  return {result.begin(), result.end()};
}

static std::vector<char> MessageBuilder::serialize(const FindDataResponseMessage &message)
{
  MessageBuilderProto::Message proto_message;
  proto_message.set_message_type(MessageBuilderProto::FindDataResponse);
  proto_message.set_request_id(boost::lexical_cast<std::string>(message.request_id));

  auto node_info = proto_message.mutable_node_info();
  node_info->set_guid(boost::lexical_cast<std::string>(message.node_info.guid));
  node_info->set_ip(message.node_info.ip);
  node_info->set_port(message.node_info.port);

  auto find_data_response_message = proto_message.mutable_find_data_response_message();

  for (auto const& n : message.nodes_info) {
    auto new_node_info = find_data_response_message->add_nodes_info();
    new_node_info->set_guid(boost::lexical_cast<std::string>(n.guid));
    new_node_info->set_ip(n.ip);
    new_node_info->set_port(n.port);
  }

  find_data_response_message->mutable_user_info()->set_guid(boost::lexical_cast<std::string>(message.user_info.guid));
  find_data_response_message->mutable_user_info()->set_domain(message.user_info.domain);

  std::string result;
  proto_message.SerializeToString(&result);

  return {result.begin(), result.end()};
}

}
}