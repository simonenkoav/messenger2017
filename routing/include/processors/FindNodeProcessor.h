#include "processors/FindProcessor.h"
#include "data_structures/Message.h"
#include "utils/MessageBuilder.h"

namespace m2 {
namespace routing {
class FindNodeProcessor: public FindProcessor
{
public:
    FindNodeProcessor(Node& node);
    ~FindNodeProcessor();

    //Message* handleMessage(Message message);
    virtual void process(uuid guid);

protected:
    // Fields

    // Methdods 
    virtual void sendRequest(NodeInfo recipient);

};
}
}