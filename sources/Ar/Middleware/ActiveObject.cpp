#include <Ar/Middleware/ActiveObject.h>
#include <Ar/Middleware/ActiveThread.h>

namespace Ar { namespace Middleware
{
    void ActiveObject::attachAndInitialize(ActiveThread *at_)
    {
        attachTo(at_);
        at()->initializeActiveObject(this);
    }
} }
