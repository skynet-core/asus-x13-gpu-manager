#ifndef asus_gpu_lib_toggle_h_
#define asus_gpu_lib_toggle_h_ 1

#include <vector>
#include <string>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace toggle
            {
                int integrated(const std::vector<std::string> &modules);
                int hybrid(const std::vector<std::string> &modules);
                int egpu(const std::vector<std::string> &modules);
            }
        }
    }
}

#endif