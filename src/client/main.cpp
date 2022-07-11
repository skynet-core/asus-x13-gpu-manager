#include <string>

#include <egpu_x13/api.h>
#include "asus-manager-proxy.h"
#include <tuple>

using namespace org::skynet;

int main()
{

    AsusManProxy asusCtrlProxy{asus::DESTINATION, asus::OBJECT_PATH};

    auto gpu = asusCtrlProxy.getCurrentMode();

    LOG_DBG("{}: {}\n", std::get<0>(gpu), std::get<1>(gpu));

    return 0;
}