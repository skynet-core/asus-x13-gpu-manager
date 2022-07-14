#include "asus-manager-adapter.h"
#include <asus-gpu-lib/api.h>
#include <string.h>
#include <fstream>
#include <sstream>

namespace org
{
  namespace skynet
  {
    namespace asus
    {

      Manager::Manager(sdbus::IConnection &connection, std::string objectPath,
                       fs::path &&wd, const std::string_view file_name,
                       const std::string_view next_file_name)
          : sdbus::AdaptorInterfaces<Base>(connection, objectPath),
            systemd_proxy_{},
            wd_{std::exchange(wd, {})},
            state_file_name_{file_name},
            next_state_file_name_{next_file_name}
      {
        registerAdaptor();
      }

      Manager::~Manager() { unregisterAdaptor(); }

      std::tuple<int32_t, std::string> Manager::make_result(int code, std::string &&msg) const
      {
        return std::make_tuple<int32_t, std::string>(std::move(code), std::move(msg));
      }

      std::tuple<int32_t, std::string> Manager::getCurrentMode()
      {
        LOG_DBG("AsusManager.getCurrentActiveGPU");
        std::string mode{};
        int32_t err = 0;
        std::tie(mode, err) = fsutils::read_mode(wd_ / state_file_name_);
        return make_result(err, std::move(mode));
      }

      std::tuple<int32_t, std::string> Manager::setMode(const std::string_view mode)
      {
        int32_t err = fsutils::write_mode(wd_ / next_state_file_name_, mode::from_string(mode));
        if (err)
        {
          return make_result(err, strerror(err));
        }
        // can be done without reboot ...
        emitRestartPrompt("please restart");
        return make_result(0, "ok");
      }

      std::tuple<int32_t, std::string> Manager::setIntegrated()
      {
        LOG_DBG("AsusManager.setIntegrated");
        return setMode("integrated");
      }

      std::tuple<int32_t, std::string> Manager::setHybrid()
      {
        LOG_DBG("AsusManager.setHybrid");
        return setMode("hybrid");
      }

      std::tuple<int32_t, std::string> Manager::setXMobile()
      {
        LOG_DBG("AsusManager.setXMobile");
        return setMode("egpu");
      }

    } // namespace asus
  }   // namespace skynet
} // namespace org