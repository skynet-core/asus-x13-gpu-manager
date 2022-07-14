#include <iostream>
#include "include/asus-gpu-lib/api.h"

using namespace org::skynet::asus::pci;
using namespace org::skynet::asus::kernel;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "argument required" << std::endl;
        return -1;
    }
    std::string action{argv[1]};
    LOG_DBG("action: {}\n", action);
    int err = -1;
    if (action == "unload")
    {
        return unload_modules({"nvidia-uvm", "nvidia-drm", "nvidia-modeset", "nvidia"});
    }
    if (action == "load")
    {
        return load_modules({"nvidia-uvm", "nvidia-drm", "nvidia-modeset", "nvidia"});
    }

    if (action == "integrated")
    {
        return set_integrated_only("0000:01:00.0");
    }

    if (action == "hybrid")
    {
        return set_hybrid_dgpu("0000:01:00.0");
    }

    if (action == "xmobile")
    {
        return set_hybrid_egpu("0000:01:00.0");
    }
    std::cerr << "action " << action << " is not supported" << std::endl;
    return -1;
}
