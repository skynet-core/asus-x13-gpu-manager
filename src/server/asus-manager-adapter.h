#ifndef asus_manager_adapter_h_
#define asus_manager_adapter_h_ 1

#include "asus-manager-adapter-glue.h"
#include <egpu_x13/api.h>
#include <signal.h>
#include <sdbus-c++/AdaptorInterfaces.h>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>
#include <vector>
#include <fstream>
#include <string_view>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string.h>
#include <systemd/sd-journal.h>

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
      static const std::vector<std::string> modules;
      AsusManager(sdbus::IConnection &connection, std::string objectPath)
          : sdbus::AdaptorInterfaces<Base>(connection, objectPath),
            systemd_proxy_{},
            uuid_gen_{}
      {
        registerAdaptor();
      }

      ~AsusManager() { unregisterAdaptor(); }

    private:
      std::tuple<int32_t, std::string> make_result(int code, std::string &&msg) const
      {
        return std::make_tuple<int32_t, std::string>(std::move(code), std::move(msg));
      }
      std::tuple<int32_t, std::string> getCurrentModeImpl()
      {
        if (!asus::pci::is_device_exists(AsusManager::device_id))
        {
          return make_result(1, "integrated");
        }
        char dgpu_disabled = asus::pci::is_dgpu_disabled();
        if (dgpu_disabled < 0)
        { // error unable to read ...
          return make_result(-1, "error: failed to read from dgpu handle");
        }
        char egpu_enabled = asus::pci::is_egpu_enabled();
        if (egpu_enabled < 0)
        {
          return make_result(-2, "error: failed to read from egpu handle");
        }
        LOG_DBG("egpu_enabled {:d} | dgpu_disabled {:d}\n", egpu_enabled, dgpu_disabled);
        if (egpu_enabled == '1')
        {
          return make_result(3, "egpu");
        }
        if (dgpu_disabled == '0') // active ...
        {
          return make_result(2, "hybrid");
        }
        return make_result(-1, "unknown");
      }

      std::tuple<int32_t, std::string> getCurrentMode() override
      {
        LOG_DBG("AsusManager.getCurrentActiveGPU");
        return getCurrentModeImpl();
      }

      std::tuple<int32_t, std::string> setModeImpl(int (*handler)(const std::string_view dev_id))
      {

        int32_t err = asus::pci::turn_off_device(device_id);
        if (err)
        {
          return make_result(err, strerror(err));
        }

        err = asus::kernel::unload_modules(modules);
        if (err)
        {
          return make_result(err, strerror(err));
        }

        err = handler(device_id);
        if (err)
        {
          return make_result(err, "switch handler failed");
        }
        return make_result(0, "ok");
      }

      std::tuple<int32_t, std::string> performTx(const std::string_view to, int (*handler)(const std::string_view dev_id))
      {
        auto tx_id = boost::uuids::to_string(uuid_gen_());
        auto curr_mode = getCurrentModeImpl();
        emitTxStart(tx_id, std::get<1>(curr_mode), static_cast<std::string>(to));
        // TODO: user promts ...
        bool dmActive = systemd_proxy_.is_display_manager_active();
        if (dmActive)
        {
          systemd_proxy_.stop_display_manager();
          // todo: wait for exit ...
        }
        auto result = setModeImpl(handler);
        if (dmActive)
        {
          systemd_proxy_.restart_display_manager();
        }
        emitTxEnd(tx_id, std::get<0>(result), std::get<1>(result));
        systemd_proxy_.Reboot();
        return result;
      }

      // TODO: make async, add more events(signals)
      std::tuple<int32_t, std::string> setIntegrated() override
      {
        LOG_DBG("AsusManager.setIntegrated");
        auto result = performTx("integrated", asus::pci::set_integrated_only);
        return result;
      }

      std::tuple<int32_t, std::string> setHybrid() override
      {
        LOG_DBG("AsusManager.setHybrid");
        auto result = performTx("hybrid", asus::pci::set_hybrid_dgpu);
        return result;
      }
      std::tuple<int32_t, std::string> setXMobile() override
      {
        LOG_DBG("AsusManager.setXMobile");
        auto result = performTx("egpu", asus::pci::set_hybrid_egpu);
        return result;
      }

      SystemdProxy systemd_proxy_;
      boost::uuids::random_generator uuid_gen_;
    };
  } // namespace skynet
} // namespace org

#endif