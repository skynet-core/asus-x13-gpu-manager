#include "pci.h"
#include "config/config.h"
#include "utils.h"
#include <fmt/core.h>
#include <fmt/format.h>
#include <fstream>
#include <filesystem>
#include <fcntl.h>

namespace fs = std::filesystem;

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace pci
            {
                // TODO: refactor ...
                int turn_off_device(const std::string_view pci_id)
                {
                    auto path = fmt::format("/sys/bus/pci/devices/{}/remove", pci_id);
                    if (!fs::exists(path))
                    { // it is ok for all cases
                        return 0;
                    }
                    std::fstream file{path, std::ios::out};
                    if (!file.is_open())
                    {
                        LOG_DBG("file {} was not open\n", path);
                        return (int)std::errc::no_such_device;
                    }
                    file.put('1');
                    if (file.fail())
                    {
                        LOG_DBG("put 1 failed\n");
                        return (int)std::errc::device_or_resource_busy;
                    }
                    return 0;
                }

                bool is_device_exists(const std::string_view pci_id)
                {
                    auto path = fmt::format("/sys/bus/pci/devices/{}/remove", pci_id);
                    return fs::exists(path);
                }

                int force_pci_rescan()
                {
                    std::fstream file{PATH_PCI_RESCAN, std::ios::out};
                    if (!file.is_open())
                    {
                        return (int)std::errc::no_such_device;
                    }
                    file.put('1');
                    if (file.fail())
                    {
                        return (int)std::errc::device_or_resource_busy;
                    }
                    return 0;
                }
                int dgpu_enable()
                {
                    std::fstream file{PATH_ASUS_DGPU_DISABLE_HANDLE, std::ios::out};
                    if (!file.is_open())
                    {
                        return (int)std::errc::no_such_device;
                    }
                    file.put('0');
                    if (file.fail())
                    {
                        return (int)std::errc::device_or_resource_busy;
                    }
                    return 0;
                }
                int dgpu_disable()
                {
                    std::fstream file{PATH_ASUS_DGPU_DISABLE_HANDLE, std::ios::out};
                    if (!file.is_open())
                    {
                        return (int)std::errc::no_such_device;
                    }
                    file.put('1');
                    if (file.fail())
                    {
                        return (int)std::errc::device_or_resource_busy;
                    }
                    return 0;
                }
                int egpu_enable()
                {
                    std::fstream file{PATH_ASUS_EGPU_ENABLE_HANDLE, std::ios::out};
                    if (!file.is_open())
                    {
                        return (int)std::errc::no_such_device;
                    }
                    file.put('1');
                    if (file.fail())
                    {
                        return (int)std::errc::device_or_resource_busy;
                    }
                    return 0;
                }
                int egpu_disable()
                {
                    std::fstream file{PATH_ASUS_EGPU_ENABLE_HANDLE, std::ios::out};
                    if (!file.is_open())
                    {
                        return (int)std::errc::no_such_device;
                    }
                    file.put('0');
                    if (file.fail())
                    {
                        return (int)std::errc::device_or_resource_busy;
                    }
                    return 0;
                }
                char is_dgpu_disabled()
                {
                    char value = -1;
                    std::ifstream file{PATH_ASUS_DGPU_DISABLE_HANDLE};
                    if (!file.is_open())
                    {
                        return value;
                    }
                    file.get(value);
                    return value;
                }
                char is_egpu_enabled()
                {
                    char value = -1;
                    std::ifstream file{PATH_ASUS_EGPU_ENABLE_HANDLE};
                    if (!file.is_open())
                    {
                        return value;
                    }
                    file.get(value);
                    return value;
                }

                int set_integrated_only(const std::string_view pci_id)
                {
                    // turn off gpu device first
                    LOG_DBG("turning off {} device\n", pci_id);
                    auto err = turn_off_device(pci_id);
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("ensure eGPU disabled\n");
                    err = egpu_disable();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("ensure dGPU disabled\n");
                    err = dgpu_disable();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    return 0;
                }
                int set_hybrid_dgpu(const std::string_view pci_id)
                {
                    // turn off gpu device first
                    LOG_DBG("turning off {} device\n", pci_id);
                    auto err = turn_off_device(pci_id);
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("ensure eGPU disabled\n");
                    err = egpu_disable();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("ensure dGPU enabled\n");
                    err = dgpu_enable();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    return 0;
                }
                int set_hybrid_egpu(const std::string_view pci_id)
                {
                    // turn off gpu device first
                    LOG_DBG("turning off {} device\n", pci_id);
                    auto err = turn_off_device(pci_id);
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("ensure dGPU disabled\n");
                    err = dgpu_disable();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("ensure eGPU enabled\n");
                    err = egpu_enable();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    return 0;
                }

                int set_compute_mode(const std::string_view pci_id)
                {
                    // turn off gpu device first
                    LOG_DBG("turning off {} device\n", pci_id);
                    auto err = turn_off_device(pci_id);
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("ensure eGPU enabled\n");
                    err = egpu_enable();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("ensure dGPU enabled\n");
                    err = dgpu_enable();
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("forcing pci rescan\n");
                    err = force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    return 0;
                }

            } // namespace pci

        } // namespace asus

    } // namespace skynet

} // namespace org
