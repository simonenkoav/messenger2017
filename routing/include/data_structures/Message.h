#pragma once
#include "data_structures/NodeInfo.h"
#include "data_structures/UserInfo.h"

#include <string>
#include <vector>
#include <list>
#include <boost/uuid/uuid.hpp>

namespace m2 {
namespace routing {

enum MessageType {
  PingRequest,
  StoreRequest,
  FindNodeRequest,
  FindDataRequest,

  PingResponse,
  StoreResponse,
  FindNodeResponse,
  FindDataResponse
};

struct Message
{
  NodeInfo node_info;
  boost::uuids::uuid request_id;
  MessageType message_type;

  Message(const NodeInfo &node_info, boost::uuids::uuid request_id, MessageType message_type);
  virtual ~Message();
};

struct PingRequestMessage : public Message
{
  PingRequestMessage(const NodeInfo &node_info, boost::uuids::uuid request_id);
};

struct StoreRequestMessage : public Message
{
  UserInfo user_info;
  StoreRequestMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, const UserInfo &user_info);
};

struct FindNodeRequestMessage : public Message
{
  boost::uuids::uuid guid;
  FindNodeRequestMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, boost::uuids::uuid guid);
};

struct FindDataRequestMessage : public Message
{
  boost::uuids::uuid guid;
  FindDataRequestMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, boost::uuids::uuid guid);
};

struct PingResponseMessage : public Message
{
  PingResponseMessage(const NodeInfo &node_info, boost::uuids::uuid request_id);
};

struct StoreResponseMessage : public Message
{
  StoreResponseMessage(const NodeInfo &node_info, boost::uuids::uuid request_id);
};

struct FindNodeResponseMessage : public Message
{
  std::list<NodeInfo> nodes_info;
  FindNodeResponseMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, const std::list<NodeInfo> &nodes_info);
};

struct FindDataResponseMessage : public Message
{
  UserInfo user_info;
  std::list<NodeInfo> nodes_info;
  FindDataResponseMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, const UserInfo &user_info, const std::list<NodeInfo> &nodes_info);
};

class MessageTypeHash
{
 public:
  template <typename T>
  std::size_t operator()(T t) const {
      return static_cast<std::size_t>(t);
  }
};

} // namespace routing
} // namespace m2