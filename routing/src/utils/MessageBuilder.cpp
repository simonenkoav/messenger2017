#include "utils/MessageBuilder.h"



namespace m2 {
namespace routing {
MessageBuilder::MessageBuilder()
{
}


MessageBuilder::~MessageBuilder()
{
}

Message MessageBuilder::deserialize(vector<char> buffer)
{
    // TODO: implement
    return Message();
}

vector<char> MessageBuilder::serialize(Message message)
{
    // TODO: implement
    return vector<char>();
}
}
}