#include "kmod.h"
#include "config/config.h"
#include <linux/module.h>
#include "logutils.h"
#include <string.h>
#include <libkmod.h>
#include <errno.h>
#include <fcntl.h>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace kernel
            {
                int unload_modules(const std::vector<std::string> &module_list)
                {
                    int res = 0;
                    int failed = 0;
                    struct kmod_ctx *ctx = kmod_new(nullptr, nullptr);
                    for (auto &&name : module_list)
                    {
                        struct kmod_module *mod;
                        res = kmod_module_new_from_name(ctx, name.c_str(), &mod);
                        if (res)
                        {
                            failed++;
                            LOG_ERROR("kmod_module_new_from_name {}: ({}){}\n",
                                    name, res, strerror(-res));
                            continue;
                        }
                        // ignore ENOENT ...
                        res = kmod_module_remove_module(mod, KMOD_REMOVE_FORCE | KMOD_REMOVE_NOWAIT);
                        if (res && (-res) != ENOENT)
                        {
                            failed++;
                            LOG_ERROR("failed to delete kernel module {}: ({}){}\n",
                                    kmod_module_get_path(mod), res,
                                    strerror(-res));
                        }
                        kmod_module_unref(mod);
                    }
                    kmod_unref(ctx);
                    return failed;
                }

                int load_modules(const std::vector<std::string> &module_list)
                {
                    int res = 0;
                    int failed = 0;
                    struct kmod_ctx *ctx = kmod_new(nullptr, nullptr);
                    for (auto &&name : module_list)
                    {
                        struct kmod_module *mod;
                        res = kmod_module_new_from_name(ctx, name.c_str(), &mod);
                        if (res)
                        {
                            failed++;
                            LOG_ERROR("kmod_module_new_from_path {}: {}\n",
                                    name, strerror(errno));
                            continue;
                        }
                        res = kmod_module_probe_insert_module(
                            mod,
                            KMOD_PROBE_FORCE_MODVERSION |
                                KMOD_PROBE_FORCE_VERMAGIC,
                            nullptr, [](struct kmod_module *m, const char *cmdline, void *data) -> int
                            { 
                                LOG_DBG("run insert: {}\n",
                                     kmod_module_get_name(m),cmdline);
                                     
                                return kmod_module_insert_module(m ,0, nullptr); },
                            nullptr, [](struct kmod_module *m, bool install, const char *options)
                            { 
                                if(install){
                                    LOG_DBG("install module: {}\n", kmod_module_get_name(m));
                                }else{
                                    LOG_DBG("insert module: {}\n", kmod_module_get_name(m));
                                } });
                        if (res)
                        {
                            failed++;
                            LOG_ERROR("failed to load kernel module {}: {}\n",
                                    kmod_module_get_name(mod), strerror(errno));
                        }
                        kmod_module_unref(mod);
                    }
                    kmod_unref(ctx);
                    return failed;
                }
            }
        } // namespace asus

    } // namespace skynet

} // namespace org
