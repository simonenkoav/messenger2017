#pragma once
#include "data_structures/NodeInfo.h"

#include <string>
#include <vector>

namespace m2 {
namespace routing {

enum MessageType;

struct Message
{
    NodeInfo node_info;
    MessageType message_type;

    Message(const NodeInfo &node_info, const MessageType message_type);
    virtual ~Message();
};

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
    FindNodeRequestMessage(const NodeInfo &node_info, uuid guid);
};

struct FindDataRequest : public Message
{
    uuid guid;
    FindNodeRequestMessage(const NodeInfo &node_info, uuid guid);
};

struct PingResponseMessage : public Message
{
    PingResponseMessage(const NodeInfo &node_info);
};

struct StoreResponsetMessage : public Message
{
    StoreResponseMessage(const NodeInfo &node_info);
};

struct FindNodeResponseMessage : public Message
{
    vector<NodeInfo> found_nodes_info;
    FindNodeRequestMessage(const NodeInfo &node_info, const vector<NodeInfo> &found_nodes_info);
};

struct FindDataResponseMessage : public Message
{
    string domain;
    FindNodeResponseMessage(const NodeInfo &node_info, const string domain);
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
