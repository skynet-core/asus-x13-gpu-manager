#ifndef asus_gpu_lib_defs_h_
#define asus_gpu_lib_defs_h_ 1

#include <string>
#include <string_view>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace manager
            {
                namespace dbus
                {
                    const std::string DESTINATION{"org.skynet.asus"};
                    const std::string OBJECT_PATH{"/org/skynet/asus/manager"};
                }
            }
            namespace pci
            {
                const std::string PATH_PCI_RESCAN{"/sys/bus/pci/rescan"};
                const std::string PATH_ASUS_DGPU_DISABLE_HANDLE{"/sys/bus/platform/devices/asus-nb-wmi/dgpu_disable"};
                const std::string PATH_ASUS_EGPU_ENABLE_HANDLE{"/sys/bus/platform/devices/asus-nb-wmi/egpu_enable"};
            }
            namespace notifications
            {
                namespace dbus
                {
                    const std::string DESTINATION{"org.freedesktop.Notifications"};
                    const std::string OBJECT_PATH{"/org/freedesktop/Notifications"};
                }
            }
            namespace systemd
            {
                namespace dbus
                {
                    const std::string DESTINATION{"org.freedesktop.systemd1"};
                    const std::string OBJECT_PATH{"/org/freedesktop/systemd1"};
                }
                namespace unit
                {
                    const std::string DISPLAY_MANAGER_SERVICE{"display-manager.service"};
                }
                namespace state
                {
                    const std::string ACTIVE{"active"};
                }
                namespace mode
                {
                    const std::string REPLACE{"replace"};
                }
            }

            namespace mode
            {
                enum class GPUMode
                {
                    UNKNOWN,
                    INTEGRATED,
                    HYBRID,
                    EGPU
                };

                std::string to_string(GPUMode mode);
                GPUMode from_string(const std::string_view mode);
            }
        }

    }
}

#endif