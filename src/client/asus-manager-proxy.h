#ifndef asus_manager_proxy_h_
#define asus_manager_proxy_h_ 1

#include <sdbus-c++/sdbus-c++.h>
#include "asus-manager-proxy-glue.h"
#include "asus-manager-proxy.h"

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
            void onRestartPrompt(const std::string &message) override
            {
            }
        };
    }
}

#endif