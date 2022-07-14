#include "asus-manager-adapter.h"
#include <asus-gpu-lib/api.h>
#include <filesystem>
#include <string.h>
#include <vector>

namespace fs = std::filesystem;

using namespace org::skynet;

#ifndef STATE_FILE_NAME
#define STATE_FILE_NAME "current"
#endif

int main(int argc, char *argv[])
{
    LOG_DBG("ASUS GPU SWITCH: start...");

    auto state_file = fs::current_path() / STATE_FILE_NAME;

    int32_t err{0};
    std::string s{};
    std::tie(s, err) = asus::fsutils::read_mode(state_file);
    if (err)
    {
        LOG_ERROR("ASUS GPU SWITCH: {}\n", strerror(err));
        return -(err);
    }

    std::string device_id{"0000:01:00.0"};
    std::vector<std::string> modules{"nvidia-uvm", "nvidia-drm", "nvidia-modeset", "nvidia"};
    auto mode = asus::mode::from_string(s);

    switch (mode)
    {
    case asus::mode::GPUMode::INTEGRATED:
        // unload modules ...
        err = asus::kernel::unload_modules(modules);
        if (err)
        {
            return err;
        }
        err = asus::pci::turn_off_device(device_id);
        if (err)
        {
            return err;
        }
        return 0;
    case asus::mode::GPUMode::HYBRID:
        // unload modules ...
        err = asus::kernel::unload_modules(modules);
        if (err)
        {
            return err;
        }
        err = asus::pci::turn_off_device(device_id);
        if (err)
        {
            return err;
        }
        err = asus::pci::force_pci_rescan();
        if (err)
        {
            return err;
        }
        err = asus::pci::egpu_disable();
        if (err)
        {
            return err;
        }
        err = asus::pci::force_pci_rescan();
        if (err)
        {
            return err;
        }
        err = asus::pci::dgpu_enable();
        if (err)
        {
            return err;
        }
        err = asus::pci::force_pci_rescan();
        if (err)
        {
            return err;
        }
        err = asus::kernel::load_modules(modules);
        if (err)
        {
            return err;
        }
        return 0;
    case asus::mode::GPUMode::EGPU:
        // unload modules ...
        err = asus::kernel::unload_modules(modules);
        if (err)
        {
            return err;
        }
        err = asus::pci::turn_off_device(device_id);
        if (err)
        {
            return err;
        }
        err = asus::pci::force_pci_rescan();
        if (err)
        {
            return err;
        }
        err = asus::pci::egpu_enable();
        if (err)
        {
            return err;
        }
        err = asus::pci::force_pci_rescan();
        if (err)
        {
            return err;
        }
        err = asus::pci::dgpu_disable();
        if (err)
        {
            return err;
        }
        err = asus::pci::force_pci_rescan();
        if (err)
        {
            return err;
        }
        err = asus::kernel::load_modules(modules);
        if (err)
        {
            return err;
        }
        return 0;
    default:
        LOG_ERROR("ASUS GPU SWITCH: unknown mode\n");
        return -(ENOENT);
    }
}