#include "processors/FindProcessor.h"
#include "data_structures/Message.h"

namespace m2 {
namespace routing {
class FindDataProcessor : protected FindProcessor
{
public:
    FindDataProcessor(Node& node, uuid request_id);
    virtual ~FindDataProcessor();

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
