#include "processors/FindProcessor.h"
#include "data_structures/Message.h"

namespace m2 {
namespace routing {
class FindDataProcessor : public FindProcessor
{
public:
    FindDataProcessor(Node& node, uuid request_id);
    virtual ~FindDataProcessor();

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
