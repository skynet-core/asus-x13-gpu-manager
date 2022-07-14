#include "asus-manager-adapter.h"
#include <asus-gpu-lib/api.h>
#include <filesystem>

namespace fs = std::filesystem;

using namespace org::skynet;

#ifndef STATE_FILE_NAME
#define STATE_FILE_NAME "current"
#endif

int main(int argc, char *argv[])
{

    auto workdir = fs::current_path();
    LOG_DBG("starting {} service ...\n", asus::dbus::DESTINATION);
    auto connection = sdbus::createSystemBusConnection(asus::dbus::DESTINATION);
    // Create asus ctrl D-Bus object.
    LOG_DBG("creating {} object ...\n", asus::dbus::OBJECT_PATH);
    org::skynet::asus::Manager svc{*connection, asus::dbus::OBJECT_PATH,
                                   std::move(workdir), STATE_FILE_NAME};

    LOG_INF("starting {} daemon ...\n", asus::dbus::DESTINATION);
    // Run the loop on the connection.
    connection->enterEventLoop();
}