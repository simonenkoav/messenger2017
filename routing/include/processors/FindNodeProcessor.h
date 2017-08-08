#include "processors/FindProcessor.h"
#include "data_structures/messages/FindNodeMessage.h"

namespace m2 {
namespace routing {
class FindNodeProcessor: protected FindProcessor, protected CommandHandler
{
public:
    FindNodeProcessor(Node& node, uuid target);
    ~FindNodeProcessor();

    //Message* handleMessage(Message message);
    virtual void handleMessage(Message message);

protected:
    // Fields

    // Methdods 
    //virtual void sendRequest(NodeSearchStruct* addressee);
    virtual Message getMessage();
};
}
}