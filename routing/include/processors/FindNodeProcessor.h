#include "processors/FindProcessor.h"
#include "data_structures/Message.h"

namespace m2 {
namespace routing {
class FindNodeProcessor: protected FindProcessor
{
public:
    FindNodeProcessor(Node& node, uuid request_id);
    ~FindNodeProcessor();

    //Message* handleMessage(Message message);
    virtual void handleMessage(Message& message);

protected:
    // Fields

    // Methdods
    virtual vector<char> getMessage();
    virtual void onSearchFinsihed();
    virtual uuid getGuid(Message& message);
};
}
}
