#include <string_view>
#include <fmt/format.h>
#include <stdio.h>
#include <iostream>
#include <errno.h>
#include <string.h>

#include "module_file.h"
#include "system.h"

module_file::module_file(std::string_view name)
{
    std::string_view kern_ver = kernel_version();
    // TODO: check file with ext .ko or .ko.xz exists
    auto path = fmt::format("/lib/modules/{}/extramodules/{}.ko.xz", kern_ver, name);
    file_ = fopen(path.c_str(), "rb");
    err_ = errno;
}

module_file::~module_file()
{
    if (file_)
    {
        fclose(file_);
    }
}

bool module_file::is_ok() const
{
    return file_ != nullptr;
}

int module_file::get_fd() const
{
    return fileno(file_);
}

std::string module_file::error() const
{
    return strerror(err_);
}