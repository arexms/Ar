#pragma once

#include <Ar/Raspi/GpioPinImplIf.h>

namespace Ar {
    namespace Raspi
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
