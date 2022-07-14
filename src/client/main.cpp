#include <string>
#include <tuple>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <CLI/CLI.hpp>
#include <asus-gpu-lib/api.h>
#include "asus-manager-proxy.h"

using namespace org::skynet;

enum class GPUMode
{
    INTEGRATED,
    HYBRID,
    EGPU,
};

std::unordered_map<std::string_view, GPUMode> &mode_by_name()
{
    static std::unordered_map<std::string_view, GPUMode> modes_by_name_ = {
        {"integrated", GPUMode::INTEGRATED},
        {"hybrid", GPUMode::HYBRID},
        {"egpu", GPUMode::EGPU},
    };
    return modes_by_name_;
}

int main(int argc, char *argv[])
{
    org::skynet::asus::log::enable();
    CLI::App app{"Asus GPU Manager CLI"};
    app.add_flag("-m,--mode", "read current GPU mode");
    std::string target_mode;
    app.add_option("-s,--set", target_mode, "target mode integrated|hybrid|egpu|compute");
    CLI11_PARSE(app, argc, argv);

    int32_t code{-1};
    std::string text{"unknown"};
   
    AsusManProxy asusCtrlProxy{asus::manager::dbus::DESTINATION, asus::manager::dbus::OBJECT_PATH};
    if (app.get_option("--mode")->as<bool>())
    {
        std::tie(code, text) = asusCtrlProxy.getCurrentMode();
        if (code < 0)
        {
            LOG_ERROR("error: failed to read current gpu mode: {} \n", text);
            return code;
        }
        PRINT("current mode: {}\n", text);
        return 0;
    }
    std::transform(target_mode.begin(), target_mode.end(), target_mode.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });
    switch (mode_by_name()[target_mode])
    {
    case GPUMode::INTEGRATED:
        std::tie(code, text) = asusCtrlProxy.setIntegrated();
        break;
    case GPUMode::HYBRID:
        std::tie(code, text) = asusCtrlProxy.setHybrid();
        break;
    case GPUMode::EGPU:
        std::tie(code, text) = asusCtrlProxy.setXMobile();
        break;
    default:
        text = "unsupported mode";
        break;
    }

    LOG_DBG("{}\n", text);

    return code;
}