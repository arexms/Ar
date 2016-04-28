#pragma once

namespace Ar {
    namespace RasPi
    {
        class GpioPinIf
        {
        public:
            enum class Type
            {
                Input = 0,
                Output = 1
            };

            GpioPinIf();
            virtual ~GpioPinIf();
            virtual void on() = 0;
            virtual void off() = 0;
            virtual bool isOn() const = 0;
            virtual int pin() const = 0;
            virtual GpioPinIf::Type type() const = 0;
        };
    }
}
