#include <asus-gpu-lib/api.h>
#include <filesystem>
#include <string.h>
#include <vector>

namespace fs = std::filesystem;

using namespace org::skynet;

#ifndef STATE_FILE_NAME
#define STATE_FILE_NAME "current"
#endif

#ifndef NEXT_STATE_FILE_NAME
#define NEXT_STATE_FILE_NAME "next"
#endif

// TODO: refactor ...

int main(int argc, char *argv[])
{
    org::skynet::asus::log::enable();
    LOG_DBG("ASUS GPU SWITCH: start...");

    auto state_file = fs::current_path() / STATE_FILE_NAME;
    auto next_state_file = fs::current_path() / NEXT_STATE_FILE_NAME;

    int32_t err{0};
    std::string s{};
    std::tie(s, err) = asus::fsutils::read_mode(state_file);
    if (err)
    {
        LOG_ERROR("ASUS GPU SWITCH: {}\n", strerror(err));
        return -(err);
    }
    auto current = asus::mode::from_string(s);

    std::tie(s, err) = asus::fsutils::read_mode(next_state_file);
    if (err)
    {
        LOG_ERROR("ASUS GPU SWITCH: {}\n", strerror(err));
        return -(err);
    }

    auto next = asus::mode::from_string(s);
    if (next == current)
    {
        LOG_DBG("nothing to change");
        return 0;
    }

    std::vector<std::string> modules{"nvidia-uvm", "nvidia-drm", "nvidia-modeset", "nvidia"};
    switch (next)
    {
    case asus::mode::GPUMode::INTEGRATED:
        err = asus::toggle::integrated(modules);
        break;
    case asus::mode::GPUMode::HYBRID:
        err = asus::toggle::hybrid(modules);
        break;
    case asus::mode::GPUMode::EGPU:
        break;
    case asus::mode::GPUMode::UNKNOWN:
        [[fallthrough]];
    default:
        LOG_ERROR("ASUS GPU SWITCH: unknown mode\n");
        return -(ENOENT);
    }

    err = asus::fsutils::write_mode(state_file, next);
    if (err)
    {
        LOG_WAR("ASUS GPU SWITCH: failed to persist new state");
        return err;
    }
    fs::remove(next_state_file);
    return 0;
}
