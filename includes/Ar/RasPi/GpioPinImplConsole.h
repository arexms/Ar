#pragma once

#include <Ar/RasPi/GpioPinImplIf.h>

namespace Ar {
    namespace RasPi
    {
        class GpioPinImplConsole : public GpioPinImplIf
        {
        public:
            GpioPinImplConsole(int pin, GpioPinIf::Type type);
            virtual ~GpioPinImplConsole();
            virtual void on();
            virtual void off();
            virtual bool isOn() const;
        };
    }
}
