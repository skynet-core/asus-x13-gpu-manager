#include <string>

#include "asus-manager-adapter.h"
#include <egpu_x13/api.h>

using namespace org::skynet;

const std::string AsusManager::device_id{"0000:01:00.0"};
const std::vector<std::string> AsusManager::modules{"nvidia-uvm", "nvidia-drm", "nvidia-modeset", "nvidia"};

int main(int argc, char *argv[])
{
    LOG_DBG("starting {} service ...\n", asus::DESTINATION);
    auto connection = sdbus::createSystemBusConnection(asus::DESTINATION);
    // Create asus ctrl D-Bus object.
    LOG_DBG("creating {} object ...\n", asus::OBJECT_PATH);
    org::skynet::AsusManager svc{*connection, asus::OBJECT_PATH};

    LOG_INF("starting {} daemon ...\n", asus::DESTINATION);
    // Run the loop on the connection.
    connection->enterEventLoop();
}