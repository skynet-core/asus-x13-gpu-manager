#include <string>

#define LOG_LEVEL 4
#include <egpu_x13/api.h>

#include <sys/syscall.h>
#include <sys/utsname.h>
#include "asus-ctrl.h"

using namespace org::skynet;

int main()
{
    // struct utsname uname_data;
    // int res = uname(&uname_data);
    // if (res != 0)
    // {
    //     return -1;
    // }

    // fmt::print("machine: {:s}\n", uname_data.machine);
    // fmt::print("sysname: {:s}\n", uname_data.sysname);
    // fmt::print("nodename: {:s}\n", uname_data.nodename);
    // fmt::print("version: {:s}\n", uname_data.version);
    // fmt::print("domainname: {:s}\n", uname_data.domainname);
    // fmt::print("release: {:s}\n", uname_data.release);
    auto mod = module_file{"nvidia-uvm"};
    if (mod.is_ok())
    {
        LOG_DBG("module fd: " + fmt::format("{}", mod.get_fd()));
    }
    else
    {
        LOG_DBG("module was not read");
    }
    // FILE *fd = fopen("", "rb");

    // int res = syscall(SYS_finit_module, 0, "", 0);
    // AsusCtrlProxy asusCtrlProxy{destinationName, objectPath};

    // auto status = asusCtrlProxy.health();

    // fmt::print("{}\n", status);

    return 0;
}