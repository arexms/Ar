#include <Ar/Raspi/GpioPinImplConsole.h>
#include <iostream>

namespace Ar {
    namespace Raspi
    {
        GpioPinImplConsole::GpioPinImplConsole(int pin, GpioPinIf::Type type)
            : GpioPinImplIf(pin, type)
        {
            std::cout << "GpioPinImplConsole::GpioPinImplConsole(): " << pin << ", " << ((type == GpioPinIf::Type::Input) ? "Input" : "Output") << "\n";
        }

        GpioPinImplConsole::~GpioPinImplConsole()
        {
            std::cout << "GpioPinImplConsole::~GpioPinImplConsole()\n";
        }

        void GpioPinImplConsole::on()
        {
            std::cout << "GpioPinImplConsole::on()\n";
        }

        void GpioPinImplConsole::off()
        {
            std::cout << "GpioPinImplConsole::off()\n";
        }

        bool GpioPinImplConsole::isOn() const
        {
            std::cout << "GpioPinImplConsole::isOn()\n";
            return (rand() % 2) == 1 ? true:false;
        }
    }
}
