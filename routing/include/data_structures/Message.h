#pragma once
#include "data_structures/NodeInfo.h"

#include <string>
#include <vector>

using namespace boost::uuids;

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
  MessageType message_type;

  Message(const NodeInfo &node_info, const MessageType message_type);
  virtual ~Message();
};



struct PingRequestMessage : public Message
{
  PingRequestMessage(const NodeInfo &node_info);
};

struct StoreRequestMessage : public Message
{
  NodeInfo store_node_info;
  StoreRequestMessage(const NodeInfo &node_info, const NodeInfo &store_node_info);
};

struct FindNodeRequestMessage : public Message
{
  uuid guid;
  FindNodeRequestMessage(const NodeInfo &node_info, const uuid guid);
};

struct FindDataRequestMessage : public Message
{
  uuid guid;
  FindDataRequestMessage(const NodeInfo &node_info, const uuid guid);
};

struct PingResponseMessage : public Message
{
  PingResponseMessage(const NodeInfo &node_info);
};

struct StoreResponseMessage : public Message
{
  StoreResponseMessage(const NodeInfo &node_info);
};

struct FindNodeResponseMessage : public Message
{
  std::vector<NodeInfo> found_nodes_info;
  FindNodeResponseMessage(const NodeInfo &node_info, const std::vector<NodeInfo> &found_nodes_info);
};

struct FindDataResponseMessage : public Message
{
  std::string domain;
  FindDataResponseMessage(const NodeInfo &node_info, const std::string domain);
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