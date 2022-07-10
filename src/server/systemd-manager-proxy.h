#ifndef asus_ctrl_systemd_proxy_h_
#define asus_ctrl_systemd_proxy_h_ 1

#define LOG_LEVEL 4

#include <egpu_x13/api.h>

#include "systemd-manager-proxy-glue.h"

#include <sdbus-c++/ProxyInterfaces.h>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace org
{
  namespace skynet
  {
    using namespace org::freedesktop::systemd1;

    class SystemdProxy : public sdbus::ProxyInterfaces<Manager_proxy>
    {

    public:
      SystemdProxy(std::string destination, std::string objectPath)
          : sdbus::ProxyInterfaces<Manager_proxy>(std::move(destination), std::move(objectPath))
      {
        registerProxy();
      }

      ~SystemdProxy() { unregisterProxy(); }

    protected:
        void onUnitNew(const std::string& id, const sdbus::ObjectPath& unit) override{

        }
        void onUnitRemoved(const std::string& id, const sdbus::ObjectPath& unit) override{

        }
        void onJobNew(const uint32_t& id, const sdbus::ObjectPath& job, const std::string& unit) override{

        }
        void onJobRemoved(const uint32_t& id, const sdbus::ObjectPath& job, const std::string& unit, const std::string& result) override{

        }
        void onStartupFinished(const uint64_t& firmware, const uint64_t& loader, const uint64_t& kernel, const uint64_t& initrd, const uint64_t& userspace, const uint64_t& total) override{

        }
        void onUnitFilesChanged() override{

        }
        void onReloading(const bool& active) override{

        }
    };
  } // namespace skynet
} // namespace org

#endif