#pragma once

namespace Ar {
    namespace Middleware
    {
        class ActiveThread;

        class ActiveObject
        {
        public:
            void attachTo(ActiveThread *at);
            
        protected:
            ActiveThread* at();

        private:
            ActiveThread *_at;
        };

        // IMPLEMENTATION
        inline void ActiveObject::attachTo(ActiveThread *at)
        {
            _at = at;
        }

        inline ActiveThread* ActiveObject::at()
        {
            return _at;
        }
    }
}
