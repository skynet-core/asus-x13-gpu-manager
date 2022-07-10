#ifndef egpu_x13_lib_h_
#define egpu_x13_lib_h_

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <ranges>

#if LOG_LEVEL > 3
#define LOG_DBG(msg)                                                                                   \
    fmt::print("[{}]: ", fmt::format(fmt::fg(fmt::color::green) | fmt::emphasis::bold, "{:^7}", "DEBUG")); \
    fmt::print("{}\n", (msg));
#else
#define LOG_DBG(msg)
#endif

#if LOG_LEVEL > 2
#define LOG_INF(msg)                                                                                   \
    fmt::print("[{}]: ", fmt::format(fmt::fg(fmt::color::yellow) | fmt::emphasis::bold, "{:^7}", "INFO")); \
    fmt::print("{}\n", (msg));
#else
#define LOG_INF(msg)
#endif

#if LOG_LEVEL > 1
#define LOG_WAR(msg)                                                                                   \
    fmt::print("[{}]: ", fmt::format(fmt::fg(fmt::color::orange) | fmt::emphasis::bold, "{:^7}", "WARN")); \
    fmt::print("{}\n", (msg));
#else
#define LOG_WAR(msg)
#endif

#if LOG_LEVEL > 0
#define LOG_ERR(msg)                                                                                 \
    fmt::print("[{}]: ", fmt::format(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "{:^7}", "ERROR")); \
    fmt::print("{}\n", (msg));
#else
#define LOG_ERR(msg)
#endif

#endif