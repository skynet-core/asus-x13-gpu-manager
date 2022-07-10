#include "system.h"

#include <sys/syscall.h>
#include <sys/utsname.h>
#include <fcntl.h>
#include <iostream>
#include <string_view>
#include <fmt/format.h>

std::string resolve_kernel_version()
{
    struct utsname utsname_data;
    int res = uname(&utsname_data);
    if (res != 0)
    {
        throw "uname: failed!";
    }
    std::string s{utsname_data.release};
    return s;
}

std::string &kernel_version()
{
    static std::string kernel_version = resolve_kernel_version();
    std::cout << kernel_version << std::endl;
    return kernel_version;
}

int load_kern_module(int file_fd, int flags);

int delete_kern_module(const std::string &name, unsigned int flags);