#pragma once

#include <Ar/Raspi/GpioPinIf.h>

namespace Ar {
    namespace Raspi
    {
        class GpioPinImplIf : public GpioPinIf
        {
        public:
            GpioPinImplIf(int pin, GpioPinIf::Type type);
            virtual ~GpioPinImplIf();
            virtual int pin() const;
            virtual GpioPinIf::Type type() const;

        private:
            int                             _pin;
            GpioPinIf::Type                 _type;
        };

        inline int GpioPinImplIf::pin() const
        {
            return _pin;
        }

        inline GpioPinImplIf::Type GpioPinImplIf::type() const
        {
            return _type;
        }
    }
}
