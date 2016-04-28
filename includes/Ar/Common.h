#ifndef Ar_Common_h__
#define Ar_Common_h__

#include <Ar/Middleware/SharedPtr.h>
namespace Ar
{
    typedef Ar::Middleware::SharedPtr< char, Middleware::PtrType_ARRAY > DataPtr;
}
#endif // Ar_Common_h__
