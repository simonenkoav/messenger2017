#include "data_structures/messages/Message.h"

namespace m2 {
namespace routing {

Message::Message(const NodeInfo &node_info, boost::uuids::uuid request_id, MessageType message_type)
    : node_info(node_info), request_id(request_id), message_type(message_type) {}

Message::~Message() {}

PingRequestMessage::PingRequestMessage(const NodeInfo &node_info, boost::uuids::uuid request_id)
   : Message(node_info, request_id, MessageType::PingRequest) {}

StoreRequestMessage::StoreRequestMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, const UserInfo &user_info)
   : Message(node_info, request_id, MessageType::StoreRequest), user_info(user_info) {}

FindNodeRequestMessage::FindNodeRequestMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, const boost::uuids::uuid guid)
   : Message(node_info, request_id, MessageType::FindNodeRequest), guid(guid) {}

FindDataRequestMessage::FindDataRequestMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, const boost::uuids::uuid guid)
   : Message(node_info, request_id, MessageType::FindDataRequest), guid(guid) {}

PingResponseMessage::PingResponseMessage(const NodeInfo &node_info, boost::uuids::uuid request_id)
   : Message(node_info, request_id, MessageType::PingResponse) {}

StoreResponseMessage::StoreResponseMessage(const NodeInfo &node_info, boost::uuids::uuid request_id)
   : Message(node_info, request_id, MessageType::StoreResponse) {}

FindNodeResponseMessage::FindNodeResponseMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, const std::list<NodeInfo> &nodes_info)
   : Message(node_info, request_id, MessageType::FindNodeResponse), nodes_info(nodes_info) {}

FindDataResponseMessage::FindDataResponseMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, const UserInfo &user_info, const std::list<NodeInfo> &nodes_info)
   : Message(node_info, request_id, MessageType::FindDataResponse), user_info(user_info), nodes_info(nodes_info) {}

} // namespace routing
} // namespace m2
