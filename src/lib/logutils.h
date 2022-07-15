#ifndef asus_gpu_lib_utils_h_
#define asus_gpu_lib_utils_h_ 1

#include "config/config.h"

#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/compile.h>
#include <fmt/ranges.h>
#include <fmt/printf.h>
#include <ranges>
#include <spdlog/spdlog.h>

namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace log
            {

                void enable();
                
                template <typename S, typename... Args>
                void print(const S &format, Args &&...args)
                {
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    fmt::print("{}\n\r", msg);
                }

                template <typename S, typename... Args>
                void debug(const S &format, Args &&...args)
                {
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    spdlog::debug(msg);
                }

                template <typename S, typename... Args>
                void info(const S &format, Args &&...args)
                {
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    spdlog::info(msg);
                }

                template <typename S, typename... Args>
                void warn(const S &format, Args &&...args)
                {
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    spdlog::warn(msg);
                }

                template <typename S, typename... Args>
                void error(const S &format, Args &&...args)
                {
                    auto msg = fmt::vformat(format, fmt::make_args_checked<Args...>(format, args...));
                    spdlog::error(msg);
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