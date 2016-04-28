#include <Ar/RasPi/GpioPinImplConsole.h>

namespace Ar {
    namespace RasPi
    {
        GpioPinImplIf::GpioPinImplIf(int pin, GpioPinIf::Type type)
            : _pin(pin)
            , _type(type)
        {
        }

        GpioPinImplIf::~GpioPinImplIf()
        {
        }
    }
}
