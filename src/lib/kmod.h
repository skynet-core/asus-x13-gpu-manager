#ifndef asus_gpu_lib_kmod_h_
#define asus_gpu_lib_kmod_h_ 1

#include <vector>
#include <string>

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