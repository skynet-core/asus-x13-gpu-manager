#ifndef asus_ctrl_c_h_
#define asus_ctrl_c_h_

#include <sdbus-c++/sdbus-c++.h>
#include "asus-ctrl-client-glue.h"

namespace org
{
    namespace skynet
    {
        using Base = org::skynet::asus::Manager_proxy;

        class AsusManProxy : public sdbus::ProxyInterfaces<Base>
        {
        public:
            AsusManProxy(std::string destination, std::string objectPath)
                : sdbus::ProxyInterfaces<Base>(std::move(destination), std::move(objectPath))
            {
                registerProxy();
            }

            ~AsusManProxy()
            {
                unregisterProxy();
            }

        protected:
            void onTxStart(const std::string &id, const std::string &info) override
            {
            }

            void onTxEnd(const std::string &id, const int32_t &code) override
            {
            }
        };
    }
}

#endif