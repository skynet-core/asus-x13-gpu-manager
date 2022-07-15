#include "fsutils.h"
#include "strutils.h"
#include <fstream>
#include <sstream>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace fsutils
            {
                int write_mode(const fs::path &path, mode::GPUMode mode)
                {
                    std::fstream file{path, std::ios::out | std::ios::trunc};
                    if (!file.is_open())
                    {
                        return ENOENT;
                    }
                    file << mode::to_string(mode);
                    file.flush();
                    if (file.fail())
                    {
                        return EPERM;
                    }
                    return 0;
                }
                std::tuple<std::string, int> read_mode(const fs::path &path)
                {
                    std::fstream file{path, std::ios::in};
                    if (!file.is_open())
                    {
                        return std::make_tuple("unknown", ENOENT);
                    }
                    std::stringstream ss;
                    ss << file.rdbuf();
                    if (file.fail())
                    {
                        return std::make_tuple("unknown", EPERM);
                    }
                    return std::make_tuple(strutils::trim(ss.str()), 0);
                }
            }
        }
    }
}
