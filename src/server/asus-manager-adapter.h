#ifndef asus_manager_adapter_h_
#define asus_manager_adapter_h_ 1

#include <egpu_x13/api.h>

#include "asus-manager-adapter-glue.h"
#include <signal.h>
#include <sdbus-c++/AdaptorInterfaces.h>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>

namespace org
{
  namespace skynet
  {

    using Base = asus::Manager_adaptor;
    using namespace org::freedesktop;
    class AsusManager : public sdbus::AdaptorInterfaces<Base>
    {

    public:
      static const std::string device_id; // 0000:01:00.0
      AsusManager(sdbus::IConnection &connection, std::string objectPath)
          : sdbus::AdaptorInterfaces<Base>(connection, objectPath),
            systemd_proxy_{}
      {
        registerAdaptor();
      }

      ~AsusManager() { unregisterAdaptor(); }

    private:
      std::tuple<int32_t, std::string> getCurrentMode() override
      {
        LOG_DBG("AsusManager.getCurrentActiveGPU");

        if (!asus::pci::is_device_exists(AsusManager::device_id))
        {
          return std::make_tuple<int32_t, std::string>(1, "integrated");
        }
        char dgpu_disabled = asus::pci::is_dgpu_disabled();
        if (dgpu_disabled < 0)
        { // error unable to read ...
          return std::make_tuple<int32_t, std::string>(-1, "error: failed to read from dgpu handle");
        }
        int egpu_enabled = asus::pci::is_egpu_enabled();
        if (egpu_enabled < 0)
        {
          return std::make_tuple<int32_t, std::string>(-2, "error: failed to read from egpu handle");
        }
        // dgpu ON && egpu OFF
        if (!dgpu_disabled && !egpu_enabled)
        {
          return std::make_tuple<int32_t, std::string>(2, "hybrid");
        }
        // dgpu OFF && egpu ON
        if (dgpu_disabled && egpu_enabled)
        {
          return std::make_tuple<int32_t, std::string>(3, "egpu");
        }
        // both ON
        return std::make_tuple<int32_t, std::string>(4, "compute");
      }
      std::tuple<int32_t, std::string> setIntegrated() override
      {
        return std::make_tuple<int32_t, std::string>(-1, "");
      }
      std::tuple<int32_t, std::string> setHybrid() override
      {
        return std::make_tuple<int32_t, std::string>(-1, "");
      }
      std::tuple<int32_t, std::string> setXMobile() override
      {
        return std::make_tuple<int32_t, std::string>(-1, "");
      }
      std::tuple<int32_t, std::string> setCompute() override
      {
        return std::make_tuple<int32_t, std::string>(-1, "");
      }

      SystemdProxy systemd_proxy_;
    };
  } // namespace skynet
} // namespace org

#endif