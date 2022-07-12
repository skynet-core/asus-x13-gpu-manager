#ifndef egpu_x13_lib_utils_h_
#define egpu_x13_lib_utils_h_ 1

#include "config/config.h"

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/compile.h>
#include <systemd/sd-journal.h>
#include <ranges>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace log
            {
                template <typename S, typename... Args>
                void print(const S &format, Args &&...args)
                {
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    fmt::print("{}\n", msg);
                }

                template <typename S, typename... Args>
                void debug(const S &format, Args &&...args)
                {
                    fmt::print("[{}]: ", fmt::format(fmt::fg(fmt::color::green) | fmt::emphasis::bold, "{:^7}", "DEBUG"));
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    fmt::print("{}", msg);
#ifdef JOURNAL_LOG
                    sd_journal_print(LOG_DEBUG, "%s", msg.c_str());
#endif
                }

                template <typename S, typename... Args>
                void info(const S &format, Args &&...args)
                {
                    fmt::print("[{}]: ", fmt::format(fmt::fg(fmt::color::yellow) | fmt::emphasis::bold, "{:^7}", "INFO"));
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    fmt::print("{}", msg);
#ifdef JOURNAL_LOG
                    sd_journal_print(LOG_INFO, "%s", msg.c_str());
#endif
                }

                template <typename S, typename... Args>
                void warn(const S &format, Args &&...args)
                {
                    fmt::print("[{}]: ", fmt::format(fmt::fg(fmt::color::orange) | fmt::emphasis::bold, "{:^7}", "WARN"));
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    fmt::print("{}", msg);
#ifdef JOURNAL_LOG
                    sd_journal_print(LOG_WARNING, "%s", msg.c_str());
#endif
                }

                template <typename S, typename... Args>
                void error(const S &format, Args &&...args)
                {
                    fmt::print("[{}]: ", fmt::format(fmt::fg(fmt::color::red) | fmt::emphasis::bold, "{:^7}", "ERROR"));
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    fmt::print("{}", msg);
#ifdef JOURNAL_LOG
                    sd_journal_print(LOG_ERR, "%s", msg.c_str());
#endif
                }
            }
        }
    } // namespace skynet

} // namespace org

#if LOG_LEVEL == 4
#define LOG_DBG(format, ...) \
    org::skynet::asus::log::debug(FMT_STRING(format) __VA_OPT__(, ) __VA_ARGS__)
#else
#define LOG_DBG(format, ...)
#endif

#if LOG_LEVEL == 3
#define LOG_INF(format, ...) \
    org::skynet::asus::log::info(FMT_STRING(format) __VA_OPT__(, ) __VA_ARGS__)
#else
#define LOG_INF(format, ...)
#endif

#if LOG_LEVEL == 2
#define LOG_WAR(format, ...) \
    org::skynet::asus::log::warn(FMT_STRING(format) __VA_OPT__(, ) __VA_ARGS__)
#else
#define LOG_WAR(format, ...)
#endif

#if LOG_LEVEL == 1
#define LOG_ERROR(format, ...) \
    org::skynet::asus::log::error(FMT_STRING(format) __VA_OPT__(, ) __VA_ARGS__)
#else
#define LOG_ERROR(format, ...)
#endif

#define PRINT(format, ...) \
    org::skynet::asus::log::print(FMT_STRING(format) __VA_OPT__(, ) __VA_ARGS__)
#endif