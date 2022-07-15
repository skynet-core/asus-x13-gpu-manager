#include "systemd-manager-proxy.h"
#include <asus-gpu-lib/api.h>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace systemd
            {
                Proxy::Proxy(const std::string &destination, const std::string &object_path)
                    : sdbus::ProxyInterfaces<systemd1::Manager_proxy>(
                          std::move(destination),
                          std::move(object_path))
                {
                }
                Proxy::Proxy() : Proxy(dbus::DESTINATION, dbus::OBJECT_PATH) {}
                Proxy::~Proxy()
                {
                    this->unregisterProxy();
                }

                void Proxy::onUnitNew(const std::string &id, const sdbus::ObjectPath &unit) {}
                void Proxy::onUnitRemoved(const std::string &id, const sdbus::ObjectPath &unit) {}
                void Proxy::onJobNew(const uint32_t &id, const sdbus::ObjectPath &job, const std::string &unit) {}
                void Proxy::onJobRemoved(const uint32_t &id, const sdbus::ObjectPath &job, const std::string &unit, const std::string &result) {}
                void Proxy::onStartupFinished(const uint64_t &firmware, const uint64_t &loader, const uint64_t &kernel, const uint64_t &initrd, const uint64_t &userspace, const uint64_t &total) {}
                void Proxy::onUnitFilesChanged() {}
                void Proxy::onReloading(const bool &active) {}
            }
        }
    }
}
