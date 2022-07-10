#include <string>

#include "asus-manager-adapter.h"
#define LOG_LEVEL 4
#include <egpu_x13/api.h>

using namespace org::skynet;


int main(int argc, char *argv[])
{
    LOG_DBG("starting " + destinationName + " service ...");
    auto connection = sdbus::createSystemBusConnection(destinationName);
    // Create asus ctrl D-Bus object.
    LOG_DBG("creating " + objectPath + " object ...");
    org::skynet::AsusManager svc{*connection, objectPath};

    LOG_INF("daemon for " + destinationName + " started");
    // Run the loop on the connection.
    connection->enterEventLoop();
}