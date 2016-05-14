#include <Ar/Raspi/GpioPinImplConsole.h>

namespace Ar {
    namespace Raspi
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
