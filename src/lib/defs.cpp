#include "defs.h"
#include "strutils.h"
#include <unordered_map>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace mode
            {
                std::string to_string(GPUMode mode)
                {
                    switch (mode)
                    {
                    case GPUMode::INTEGRATED:
                        return "integrated";
                    case GPUMode::HYBRID:
                        return "hybrid";
                    case GPUMode::EGPU:
                        return "egpu";
                    default:
                        return "unknown";
                    }
                }

                std::unordered_map<std::string_view, GPUMode> gpumode_mapping = {
                    {"integrated", GPUMode::INTEGRATED},
                    {"hybrid", GPUMode::HYBRID},
                    {"egpu", GPUMode::EGPU}};

                GPUMode from_string(const std::string_view mode)
                {
                    auto m = strutils::trim(strutils::to_lower(mode));
                    if (gpumode_mapping.contains(m))
                    {
                        return gpumode_mapping[m];
                    }
                    return GPUMode::UNKNOWN;
                }
            }
        }
    }
}