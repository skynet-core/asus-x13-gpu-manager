#ifndef asus_gpu_manager_systemd_proxy_h_
#define asus_gpu_manager_systemd_proxy_h_ 1

#include <string>

#include <sdbus-c++/ProxyInterfaces.h>
#include <sdbus-c++/sdbus-c++.h>

#include "systemd-manager-proxy-glue.h"

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace systemd
            {
                using namespace org::freedesktop;

                class Proxy : public sdbus::ProxyInterfaces<systemd1::Manager_proxy>
                {
                public:
                    Proxy(const std::string &destination, const std::string &object_path);
                    Proxy();
                    ~Proxy();

                protected:
                    void onUnitNew(const std::string &id, const sdbus::ObjectPath &unit) override;
                    void onUnitRemoved(const std::string &id, const sdbus::ObjectPath &unit) override;
                    void onJobNew(const uint32_t &id, const sdbus::ObjectPath &job, const std::string &unit) override;
                    void onJobRemoved(const uint32_t &id, const sdbus::ObjectPath &job, const std::string &unit, const std::string &result) override;
                    void onStartupFinished(const uint64_t &firmware, const uint64_t &loader, const uint64_t &kernel, const uint64_t &initrd, const uint64_t &userspace, const uint64_t &total) override;
                    void onUnitFilesChanged() override;
                    void onReloading(const bool &active) override;
                };
            } // namespace systemd
        }

    } // namespace skynet
} // namespace org

#endif