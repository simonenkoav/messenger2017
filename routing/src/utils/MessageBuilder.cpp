#include "utils/MessageBuilder.h"

namespace m2 {
namespace routing {
MessageBuilder::MessageBuilder()
{
}


MessageBuilder::~MessageBuilder()
{
}

std::unique_ptr<Message> MessageBuilder::deserialize(vector<char> &buffer)
{
    MessageBuilder::Message message;
    std::string buffer_string(buffer.begin(), buffer.end());
    message.ParseFromString(buffer_string);
    NodeInfo node_info{message.node_info().guid(), message.node_info().ip(), message.node_info().port()};
    if (message.message_type() == MessageBuilder::PingRequest) {
        return new PingRequestMessage(node_info);
    } else if (message,message_type() == MessageBuilder::StoreRequest){
        NodeInfo store_node_info{
            message.store_request_message().store_node_info().guid(),
            message.store_request_message().store_node_info().ip(),
            message.store_request_message().store_node_info().port(),
        }
        return new StoreRequestMessage(node_info, store_node_info);
    } else if (message.message_type() == MessageBuilder::FindNodeRequest){
        return new FindNodeRequestMessage(node_info, message.find_node_reqest_message().guid());
    } else if (message.message_type() == MessageBuilder::FindDataRequest) {
        return new FindDataRequestMessage(node_info, message.find_data_reqest_message().guid());
    } else if (message.message_type() == MessageBuilder::PingResponse) {
        return new PingResponseMessage(node_info);
    } else if (message.message_type() == MessageBuilder::StoreResponse) {
        return new StoreResponseMessage(node_info);
    } else if (message.message_type() == MessageBuilder::FindNodeResponse) {
        vector<NodeInfo> found_nodes_info;
        for (int i = 0; i < message.find_node_response_message().found_nodes_info_size(); ++i) {
            auto& node_info_proto = message.find_node_response_message().found_nodes_info(i);
            found_nodes_info.push_back(NodeInfo{node_info_proto.guid(), node_info_proto.ip(), node_info_proto.port()});
        }
        return new FindNodeResponseMessage(node_info, found_nodes_info);
    } else if (message.message_type() == MessageBuilder::FindDataResponse) {
        return new FindDataRequestMessage(node_info, message.find_data_response_message().guid());
    } else {
        throw std::runtime_error("Unexpected message type");
    }
}

vector<char> MessageBuilder::serialize(const PingRequestMessage &message)
{
    MessageBuilder::Message proto_message;
    proto_message.set_message_type(MessageBuilder::PingRequest);

    auto node_info = proto_message.mutable_node_info();
    node_info->set_guid(message.node_info.uuid);
    node_info->set_ip(message.node_info.ip);
    node_info->set_port(message.node_info.port);

    std::string result;
    proto_message.SerializeToString(&result);

    return {str.begin(), str.end()};
}

vector<char> MessageBuilder::serialize(const StoreRequestMessage &message)
{
    MessageBuilder::Message proto_message;
    proto_message.set_message_type(MessageBuilder::StoreRequest);

    auto node_info = proto_message.mutable_node_info();
    node_info->set_guid(message.node_info.uuid);
    node_info->set_ip(message.node_info.ip);
    node_info->set_port(message.node_info.port);

    auto store_request_message = proto_message.mutable_store_request_message();
    store_request_message->set_guid(message.store_node_info.uuid);
    store_request_message->set_ip(message.store_node_info.ip);
    store_request_message->set_port(message.store_node_info.port);

    std::string result;
    proto_message.SerializeToString(&result);

    return {str.begin(), str.end()};
}

vector<char> MessageBuilder::serialize(const FindNodeRequestMessage &message)
{
    MessageBuilder::Message proto_message;
    proto_message.set_message_type(MessageBuilder::FindNodeRequest);

    auto node_info = proto_message.mutable_node_info();
    node_info->set_guid(message.node_info.uuid);
    node_info->set_ip(message.node_info.ip);
    node_info->set_port(message.node_info.port);

    auto find_node_reqest_message = proto_message.mutable_find_node_reqest_message();
    find_node_reqest_message->set_guid(message.guid);

    std::string result;
    proto_message.SerializeToString(&result);

    return {str.begin(), str.end()};
}

vector<char> MessageBuilder::serialize(const FindDataRequestMessage &message)
{
    MessageBuilder::Message proto_message;
    proto_message.set_message_type(MessageBuilder::FindDataRequest;

    auto node_info = proto_message.mutable_node_info();
    node_info->set_guid(message.node_info.uuid);
    node_info->set_ip(message.node_info.ip);
    node_info->set_port(message.node_info.port);

    auto find_data_request_message = proto_message.find_data_request_message();
    find_data_request_message->set_guid(message.guid);

    std::string result;
    proto_message.SerializeToString(&result);

    return {str.begin(), str.end()};
}

vector<char> MessageBuilder::serialize(const PingResponseMessage &message)
{
    MessageBuilder::Message proto_message;
    proto_message.set_message_type(MessageBuilder::PingResponse);

    auto node_info = proto_message.mutable_node_info();
    node_info->set_guid(message.node_info.uuid);
    node_info->set_ip(message.node_info.ip);
    node_info->set_port(message.node_info.port);

    std::string result;
    proto_message.SerializeToString(&result);

    return {str.begin(), str.end()};
}

vector<char> MessageBuilder::serialize(const StoreResponsetMessage &message)
{
    MessageBuilder::Message proto_message;
    proto_message.set_message_type(MessageBuilder::StoreResponse);

    auto node_info = proto_message.mutable_node_info();
    node_info->set_guid(message.node_info.uuid);
    node_info->set_ip(message.node_info.ip);
    node_info->set_port(message.node_info.port);

    std::string result;
    proto_message.SerializeToString(&result);

    return {str.begin(), str.end()};
}

vector<char> MessageBuilder::serialize(const FindNodeResponseMessage &message)
{
    MessageBuilder::Message proto_message;
    proto_message.set_message_type(MessageBuilder::FindNodeResponse);

    auto node_info = proto_message.mutable_node_info();
    node_info->set_guid(message.node_info.uuid);
    node_info->set_ip(message.node_info.ip);
    node_info->set_port(message.node_info.port);

    auto find_node_response_message = proto_message.mutable_find_node_response_message();
    for (int i = 0; i < message.found_nodes_info.size(); ++i) {
        auto node_info = proto_message.add_found_nodes_info();
        node_info->set_guid(message.found_nodes_info[i].uuid);
        node_info->set_ip(message.found_nodes_info[i].ip);
        node_info->set_port(message.found_nodes_info[i].port);
    }

    std::string result;
    proto_message.SerializeToString(&result);

    return {str.begin(), str.end()};
}

vector<char> MessageBuilder::serialize(const FindDataResponseMessage &message)
{
    MessageBuilder::Message proto_message;
    proto_message.set_message_type(MessageBuilder::FindDataResponse);

    auto node_info = proto_message.mutable_node_info();
    node_info->set_guid(message.node_info.uuid);
    node_info->set_ip(message.node_info.ip);
    node_info->set_port(message.node_info.port);

    auto find_data_response_message = proto_message.mutable_find_data_response_message();
    find_data_response_message->set_domain(message.domain.);

    std::string result;
    proto_message.SerializeToString(&result);

    return {str.begin(), str.end()};
}
}
}
