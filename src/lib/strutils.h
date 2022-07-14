#ifndef asus_gpu_lib_strutils_h_
#define asus_gpu_lib_strutils_h_ 1

#include <string>
#include <algorithm>
#include <cctype>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace strutils
            {
                std::string ltrim(const std::string &s);

                std::string rtrim(const std::string &s);

                std::string trim(const std::string &s);

                std::string to_lower(const std::string_view s);
            }
        }
    }
}

#endif