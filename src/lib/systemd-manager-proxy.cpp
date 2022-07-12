#include "config/config.h"
#include "utils.h"
#include "systemd-manager-proxy.h"

namespace org
{
    namespace skynet
    {
        using namespace org::freedesktop;

        SystemdProxy::~SystemdProxy() { this->unregisterProxy(); }

        SystemdProxy::SystemdProxy(const std::string &destination,
                                   const std::string &object_path)
            : sdbus::ProxyInterfaces<systemd1::Manager_proxy>(std::move(destination),
                                                              std::move(object_path)),
              lookup_names_{systemd1::unit::DISPLAY_MANAGER_SERVICE}
        {
            this->registerProxy();
        }

        SystemdProxy::SystemdProxy()
            : SystemdProxy(systemd1::DESTINATION, systemd1::OBJECT_PATH) {}

        bool SystemdProxy::is_display_manager_active()
        {
            // see https://www.freedesktop.org/wiki/Software/systemd/dbus/
            auto jobs = this->ListUnitsByNames(lookup_names_);
            for (auto &&job : jobs)
            {
                if (job.get<3>() == systemd1::state::ACTIVE)
                {
                    return true;
                }
            }
            return false;
        }

        sdbus::ObjectPath SystemdProxy::stop_display_manager()
        {
            // returns ObjectPath ...
            return this->StopUnit(systemd1::unit::DISPLAY_MANAGER_SERVICE, systemd1::mode::REPLACE);
        }

        sdbus::ObjectPath SystemdProxy::restart_display_manager()
        {
            return this->RestartUnit(systemd1::unit::DISPLAY_MANAGER_SERVICE, systemd1::mode::REPLACE);
        }

        void SystemdProxy::onUnitNew(const std::string &id, const sdbus::ObjectPath &unit)
        {
            // LOG_DBG("SystemdProxy::onUnitNew");
        }
        void SystemdProxy::onUnitRemoved(const std::string &id, const sdbus::ObjectPath &unit)
        {
            // LOG_DBG("SystemdProxy::onUnitRemoved");
        }
        void SystemdProxy::onJobNew(const uint32_t &id, const sdbus::ObjectPath &job, const std::string &unit)
        {
            // LOG_DBG("SystemdProxy::onJobNew");
        }
        void SystemdProxy::onJobRemoved(const uint32_t &id, const sdbus::ObjectPath &job, const std::string &unit, const std::string &result)
        {
            // LOG_DBG("SystemdProxy::onJobRemoved");
        }
        void SystemdProxy::onStartupFinished(const uint64_t &firmware, const uint64_t &loader, const uint64_t &kernel, const uint64_t &initrd, const uint64_t &userspace, const uint64_t &total)
        {
            // LOG_DBG("SystemdProxy::onStartupFinished");
        }
        void SystemdProxy::onUnitFilesChanged()
        {
            // LOG_DBG("SystemdProxy::onUnitFilesChanged");
        }
        void SystemdProxy::onReloading(const bool &active)
        {
            // LOG_DBG("SystemdProxy::onReloading");
        }
    }
}