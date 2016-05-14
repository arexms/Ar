#include <Ar/Raspi/GpioPin.h>
#include <Ar/Raspi/GpioPinImplIf.h>
#include <chrono>

namespace Ar {
    namespace Raspi
    {
        GpioPin::GpioPin(GpioPinImplIf *impl)
            : _impl(impl)
            , _destroy(false)
        {
        }

        GpioPin::~GpioPin()
        {
            _destroy = true;
            _onChangeThread->join();
        }

        void GpioPin::on()
        {
            impl()->on();
        }

        void GpioPin::off()
        {
            impl()->off();
        }

        bool GpioPin::isOn() const
        {
            return impl()->isOn();
        }

        void GpioPin::onChange(std::function<void(bool)> watcher)
        {
            _onChangeThread.reset(new std::thread([this, watcher]()
            {
                bool value = isOn();
                while(!_destroy)
                {
                    if (isOn() != value)
                    {
                        value = !value;
                        watcher(value);
                    }
                    using namespace std::literals;
                    std::this_thread::sleep_for(1s);
                }
            }));
            
        }

        int GpioPin::pin() const
        {
            return impl()->pin();
        }

        GpioPinIf::Type GpioPin::type() const
        {
            return impl()->type();
        }
    }
}
