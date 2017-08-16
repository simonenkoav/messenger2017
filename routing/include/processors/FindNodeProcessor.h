#include "processors/FindProcessor.h"
#include "data_structures/Message.h"

namespace m2 {
namespace routing {
class FindNodeProcessor: public FindProcessor
{
public:
    FindNodeProcessor(Node& node, uuid request_id);
    virtual ~FindNodeProcessor();

    //Message* handleMessage(const Message message);
    virtual void handleMessage(const Message& message) override;

protected:
    // Fields

    // Methdods
    virtual vector<char> getMessage();
    virtual void onSearchFinsihed();
    virtual uuid getGuid(const Message& message) override;
};
}
}
