#ifndef egpu_x13_lib_config_h_
#define egpu_x13_lib_config_h_

#include <string>

namespace org
{
    namespace skynet
    {
        const std::string destinationName{"org.skynet.asus"};
        const std::string objectPath{"/org/skynet/asus/manager"};
        const std::string systemdDestName {"org.freedesktop.systemd1"};
        const std::string systemdObjPath {"/org/freedesktop/systemd1/manager"};
    }
}

#endif