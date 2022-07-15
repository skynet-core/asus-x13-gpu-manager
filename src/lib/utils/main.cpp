#include <iostream>
#include "include/asus-gpu-lib/api.h"

using namespace org::skynet::asus;
using namespace org::skynet::asus::kernel;

int main(int argc, char *argv[])
{
    org::skynet::asus::log::enable();
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
        return toggle::integrated({"nvidia-uvm", "nvidia-drm", "nvidia-modeset", "nvidia"});
    }

    if (action == "hybrid")
    {
        return toggle::hybrid({"nvidia-uvm", "nvidia-drm", "nvidia-modeset", "nvidia"});
    }

    if (action == "egpu")
    {
        return toggle::egpu({"nvidia-uvm", "nvidia-drm", "nvidia-modeset", "nvidia"});
    }
    std::cerr << "action " << action << " is not supported" << std::endl;
    return -1;
}
