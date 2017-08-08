#include "processors/FindProcessor.h"
#include "data_structures/Message.h"

namespace m2 {
namespace routing {
class FindNodeProcessor: protected FindProcessor, protected CommandHandler
{
public:
    FindNodeProcessor(Node& node, uuid request_id, uuid target);
    ~FindNodeProcessor();

    //Message* handleMessage(Message message);
    virtual void handleMessage(Message& message);

protected:
    // Fields

    // Methdods
    virtual vector<char> getMessage();
    virtual void onSearchFinsihed();
};
}
}
