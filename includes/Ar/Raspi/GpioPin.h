#pragma once

#include <Ar/Raspi/GpioPinIf.h>
#include <memory>
#include <functional>
#include <thread>

namespace Ar {
    namespace Raspi
    {
        class GpioPinImplIf;

        class GpioPin : public GpioPinIf
        {
        public:
            template < typename ImplType >
            static GpioPin create(int pin, GpioPinIf::Type type);

            virtual ~GpioPin();
            virtual void on();
            virtual void off();
            virtual bool isOn() const;
            void onChange(std::function<void(bool)> watcher);

            virtual int pin() const;
            GpioPinIf::Type type() const;

        protected:
            GpioPin(GpioPinImplIf *impl);
            std::shared_ptr<GpioPinImplIf> impl();
            const std::shared_ptr<GpioPinImplIf> impl() const;

        private:
            std::shared_ptr<GpioPinImplIf>  _impl;
            std::shared_ptr<std::thread>    _onChangeThread;
            bool _destroy;
        };

        template < typename ImplType >
        GpioPin GpioPin::create(int pin, GpioPinIf::Type type)
        {
            return GpioPin(new ImplType(pin, type));
        }

        inline std::shared_ptr<GpioPinImplIf> GpioPin::impl()
        {
            return _impl;
        }

        inline const std::shared_ptr<GpioPinImplIf> GpioPin::impl() const
        {
            return _impl;
        }
    }
}
