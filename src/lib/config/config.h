#ifndef egpu_x13_lib_config_h_
#define egpu_x13_lib_config_h_ 1

#if defined(LEVEL_DEBUG)
#define LOG_LEVEL 4
#elif defined(LEVEL_INFO)
#define LOG_LEVEL 3
#elif defined(LEVEL_WARN)
#define LOG_LEVEL 2
#elif defined(LEVEL_ERROR)
#define LOG_LEVEL 1
#endif

#include <string>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            const std::string DESTINATION{"org.skynet.asus"};
            const std::string OBJECT_PATH{"/org/skynet/asus/manager"};
            namespace pci
            {
                const std::string PATH_PCI_RESCAN{"/sys/bus/pci/rescan"};
                const std::string PATH_ASUS_DGPU_DISABLE_HANDLE{"/sys/bus/platform/devices/asus-nb-wmi/dgpu_disable"};
                const std::string PATH_ASUS_EGPU_ENABLE_HANDLE{"/sys/bus/platform/devices/asus-nb-wmi/egpu_enable"};
            }
        }

    }
    namespace freedesktop
    {
        namespace systemd1
        {
            const std::string DESTINATION{"org.freedesktop.systemd1"};
            const std::string OBJECT_PATH{"/org/freedesktop/systemd1"};
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
    }
}

#endif