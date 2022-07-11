#ifndef egpu_x13_lib_pci_h_
#define egpu_x13_lib_pci_h_ 1

#include <string_view>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace pci
            {
                bool is_device_exists(const std::string_view pci_id);
                int turn_off_device(const std::string_view pci_id);
                int force_pci_rescan();
                int dgpu_enable();
                int dgpu_disable();
                int egpu_enable();
                int egpu_disable();
                char is_dgpu_disabled();
                char is_egpu_enabled();

                int set_integrated_only(const std::string_view pci_id);
                int set_hybrid_dgpu(const std::string_view pci_id);
                int set_hybrid_egpu(const std::string_view pci_id);
                int set_compute_mode(const std::string_view pci_id);
            }
        }
    }
}

#endif