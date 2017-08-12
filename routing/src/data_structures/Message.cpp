#include "data_structures/Message.h"

namespace m2 {
namespace routing {

Message::Message(const NodeInfo &node_info, MessageType message_type)
    : node_info(node_info), request_id(boost::uuids::basic_random_generator<boost::mt19937>()()), message_type(message_type) {}

Message::Message(const NodeInfo &node_info, MessageType message_type, const boost::uuids::uuid request_id)
    : node_info(node_info), request_id(request_id), message_type(message_type) {}

Message::~Message() {}

NotRespondingMessage::NotRespondingMessage(const NodeInfo &node_info, boost::uuids::uuid request_id)
    : Message(node_info, MessageType::NotResponding, request_id) {}

NotFoundMessage::NotFoundMessage(const NodeInfo &node_info, boost::uuids::uuid request_id, boost::uuids::uuid guid)
    : Message(node_info, MessageType::NotFound, request_id), guid(guid) {}

PingRequestMessage::PingRequestMessage(const NodeInfo &node_info)
    : Message(node_info, MessageType::PingRequest) {}

PingRequestMessage::PingRequestMessage(const NodeInfo &node_info, const boost::uuids::uuid request_id)
    : Message(node_info, MessageType::PingRequest, request_id) {}

StoreRequestMessage::StoreRequestMessage(const NodeInfo &node_info, const UserInfo &user_info)
    : Message(node_info, MessageType::StoreRequest), user_info(user_info) {}

StoreRequestMessage::StoreRequestMessage(const NodeInfo &node_info, const boost::uuids::uuid request_id, const UserInfo &user_info)
    : Message(node_info, MessageType::StoreRequest, request_id), user_info(user_info) {}

FindNodeRequestMessage::FindNodeRequestMessage(const NodeInfo &node_info, const boost::uuids::uuid guid)
    : Message(node_info, MessageType::FindNodeRequest), guid(guid) {}

FindNodeRequestMessage::FindNodeRequestMessage(const NodeInfo &node_info, const boost::uuids::uuid request_id,
    const boost::uuids::uuid guid)
    : Message(node_info, MessageType::FindNodeRequest, request_id), guid(guid) {}

FindDataRequestMessage::FindDataRequestMessage(const NodeInfo &node_info, const boost::uuids::uuid guid)
    : Message(node_info, MessageType::FindDataRequest), guid(guid) {}

FindDataRequestMessage::FindDataRequestMessage(const NodeInfo &node_info, const boost::uuids::uuid request_id, const boost::uuids::uuid guid)
    : Message(node_info, MessageType::FindDataRequest, request_id), guid(guid) {}

PingResponseMessage::PingResponseMessage(const NodeInfo &node_info, const boost::uuids::uuid request_id)
    : Message(node_info, MessageType::PingResponse, request_id) {}

StoreResponseMessage::StoreResponseMessage(const NodeInfo &node_info, const boost::uuids::uuid request_id)
    : Message(node_info, MessageType::StoreResponse, request_id) {}

FindNodeResponseMessage::FindNodeResponseMessage(const NodeInfo &node_info, const boost::uuids::uuid request_id,
    const std::list<NodeInfo> &nodes_info)
    : Message(node_info, MessageType::FindNodeResponse, request_id), nodes_info(nodes_info) {}

FindDataResponseMessage::FindDataResponseMessage(const NodeInfo &node_info, const boost::uuids::uuid request_id,
    const UserInfo &user_info, const std::list<NodeInfo> &nodes_info)
    : Message(node_info, MessageType::FindDataResponse, request_id), user_info(user_info), nodes_info(nodes_info) {}

} // namespace routing
} // namespace m2