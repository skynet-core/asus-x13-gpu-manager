#include "toggle.h"
#include "pci.h"
#include "kmod.h"
#include "logutils.h"

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace toggle
            {
                int integrated(const std::vector<std::string> &modules)
                {
                    LOG_DBG("toggle integrated: unload modules...");
                    // unload modules ...
                    int err = asus::kernel::unload_modules(modules);
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("toggle integrated: check egpu status...");
                    char status = asus::pci::is_egpu_enabled();
                    if (status < 0)
                    {
                        return static_cast<int>(status);
                    }
                    if (status == '1')
                    {
                        LOG_DBG("toggle integrated: disable egpu...");
                        err = asus::pci::egpu_disable();
                        if (err)
                        {
                            return err;
                        }
                    }

                    LOG_DBG("toggle integrated: check dgpu status...");
                    status = asus::pci::is_dgpu_disabled();
                    if (status < 0)
                    {
                        return static_cast<int>(status);
                    }
                    if (status == '0')
                    {
                        LOG_DBG("toggle integrated: disable dgpu...");
                        err = asus::pci::dgpu_disable();
                        if (err)
                        {
                            return err;
                        }
                    }

                    LOG_DBG("toggle integrated: force rescan...");
                    err = asus::pci::force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    return 0;
                }
                int hybrid(const std::vector<std::string> &modules)
                {
                    LOG_DBG("toggle hybrid: unload modules...");
                    int err = asus::kernel::unload_modules(modules);
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("toggle  hybrid: check egpu status...");
                    char status = asus::pci::is_egpu_enabled();
                    if (status < 0)
                    {
                        return static_cast<int>(status);
                    }
                    if (status == '1')
                    {
                        LOG_DBG("toggle hybrid: disable egpu ...");
                        err = asus::pci::egpu_disable();
                        if (err)
                        {
                            return err;
                        }
                    }
                    LOG_DBG("toggle hybrid: check dgpu status ...");
                    status = asus::pci::is_dgpu_disabled();
                    if (status < 0)
                    {
                        return static_cast<int>(status);
                    }
                    if (status == '1')
                    {
                        LOG_DBG("toggle hybrid: enable dgpu...");
                        err = asus::pci::dgpu_enable();
                        if (err)
                        {
                            return err;
                        }
                    }
                    LOG_DBG("toggle hybrid: force pci rescan...");
                    err = asus::pci::force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    return 0;
                }
                int egpu(const std::vector<std::string> &modules)
                {
                    // unload modules ...
                    LOG_DBG("toggle egpu: unload modules...");
                    int err = asus::kernel::unload_modules(modules);
                    if (err)
                    {
                        return err;
                    }
                    LOG_DBG("toggle egpu: check egpu status...");
                    char status = asus::pci::is_egpu_enabled();
                    if (status < 0)
                    {
                        return static_cast<int>(status);
                    }
                    if (status == '0')
                    {
                        LOG_DBG("toggle egpu: enable egpu...");
                        err = asus::pci::egpu_enable();
                        if (err)
                        {
                            return err;
                        }
                    }
                    LOG_DBG("toggle egpu: check dgpu status...");
                    status = asus::pci::is_dgpu_disabled();
                    if (status < 0)
                    {
                        return static_cast<int>(status);
                    }
                    if (status == '1')
                    {
                        LOG_DBG("toggle egpu: enable dgpu(required)...");
                        err = asus::pci::dgpu_enable();
                        if (err)
                        {
                            return err;
                        }
                    }
                    LOG_DBG("toggle egpu: force pci rescan ...");
                    err = asus::pci::force_pci_rescan();
                    if (err)
                    {
                        return err;
                    }
                    return 0;
                }
            }
        }
    }
}