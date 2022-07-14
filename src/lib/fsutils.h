#ifndef asus_gpu_lib_fsutils_h_
#define asus_gpu_lib_fsutils_h_ 1

#include <filesystem>
#include <tuple>
#include "defs.h"

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace fsutils
            {
                namespace fs = std::filesystem;
                int write_mode(const fs::path &path, mode::GPUMode mode);
                std::tuple<std::string, int> read_mode(const fs::path &path);
            }
        }
    }
}

#endif