#include "logutils.h"
#include <spdlog/sinks/systemd_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <memory>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dist_sink.h>


namespace org
{
    namespace skynet
    {
        namespace asus
        {
            namespace log
            {
                void enable()
                {
                    auto systemd_sink = std::make_shared<spdlog::sinks::systemd_sink_st>();
                    auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
                    auto dist_sink = std::make_shared<spdlog::sinks::dist_sink_st>();
                    dist_sink->add_sink(systemd_sink);
                    dist_sink->add_sink(stdout_sink);

                    auto logger = std::make_shared<spdlog::logger>("asus-gpu-manager", dist_sink);

                    spdlog::set_default_logger(logger);

                    spdlog::set_level(spdlog::level::trace);
                }
            }
        }
    }
}
