#ifndef egpu_x13_lib_systemd_proxy_h_
#define egpu_x13_lib_systemd_proxy_h_ 1

#include "systemd-manager-proxy-glue.h"
#include <sdbus-c++/ProxyInterfaces.h>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <vector>

namespace org
{
  namespace skynet
  {
    using namespace org::freedesktop;

    class SystemdProxy : public sdbus::ProxyInterfaces<systemd1::Manager_proxy>
    {
    public:
      SystemdProxy(const std::string &destination, const std::string &object_path);

      SystemdProxy();

      ~SystemdProxy();

      bool is_display_manager_active();
      sdbus::ObjectPath stop_display_manager();
      sdbus::ObjectPath restart_display_manager();

    protected:
      void onUnitNew(const std::string &id, const sdbus::ObjectPath &unit) override;
      void onUnitRemoved(const std::string &id, const sdbus::ObjectPath &unit) override;
      void onJobNew(const uint32_t &id, const sdbus::ObjectPath &job, const std::string &unit) override;
      void onJobRemoved(const uint32_t &id, const sdbus::ObjectPath &job, const std::string &unit, const std::string &result) override;
      void onStartupFinished(const uint64_t &firmware, const uint64_t &loader, const uint64_t &kernel, const uint64_t &initrd, const uint64_t &userspace, const uint64_t &total) override;
      void onUnitFilesChanged() override;
      void onReloading(const bool &active) override;

    private:
      std::vector<std::string> lookup_names_;
    };
  } // namespace skynet
} // namespace org

#endif