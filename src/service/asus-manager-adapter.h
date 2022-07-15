#ifndef asus_manager_adapter_h_
#define asus_manager_adapter_h_ 1

#include "asus-manager-adapter-glue.h"
#include "systemd-manager-proxy.h"

#include <sdbus-c++/AdaptorInterfaces.h>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>
#include <string_view>
#include <filesystem>

namespace org
{
  namespace skynet
  {
    namespace asus
    {

      using Base = asus::Manager_adaptor;
      using SystemdProxy = asus::systemd::Proxy;

      namespace fs = std::filesystem;

      class Manager : public sdbus::AdaptorInterfaces<Base>
      {

      public:
        Manager(sdbus::IConnection &connection, std::string objectPath,
                fs::path &&wd, const std::string_view file,
                const std::string_view next);

        ~Manager();

      private:
        std::tuple<int32_t, std::string> make_result(int code, std::string &&msg) const;

        std::tuple<int32_t, std::string> getCurrentMode() override;

        std::tuple<int32_t, std::string> setMode(const std::string_view mode);

        std::tuple<int32_t, std::string> setIntegrated() override;

        std::tuple<int32_t, std::string> setHybrid() override;

        std::tuple<int32_t, std::string> setXMobile() override;

        SystemdProxy systemd_proxy_;
        fs::path wd_;
        std::string state_file_name_;
        std::string next_state_file_name_;        
      };

    } // namespace asus
  }   // namespace skynet
} // namespace org

#endif