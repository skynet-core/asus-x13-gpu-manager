#ifndef egpu_x13_lib_kmod_h_
#define egpu_x13_lib_kmod_h_ 1

#include <vector>
#include <string>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace kernel
            {
                int unload_modules(const std::vector<std::string> &module_list);

                int load_modules(const std::vector<std::string> &module_list);
            }
        } // namespace asus

    } // namespace skynet

} // namespace org

#endif