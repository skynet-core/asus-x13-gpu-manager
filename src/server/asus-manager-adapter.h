#ifndef asus_manager_adapter_h_
#define asus_manager_adapter_h_ 1

#define LOG_LEVEL 4

#include <egpu_x13/api.h>

#include "asus-manager-adapter-glue.h"
#include <sdbus-c++/AdaptorInterfaces.h>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

#include "systemd-manager-proxy.h"

namespace org
{
  namespace skynet
  {
    using Base = asus::Manager_adaptor;
    class AsusManager : public sdbus::AdaptorInterfaces<Base>
    {

    public:
      AsusManager(sdbus::IConnection &connection, std::string objectPath)
          : sdbus::AdaptorInterfaces<Base>(connection, objectPath)
      {
        registerAdaptor();
      }

      ~AsusManager() { unregisterAdaptor(); }

    protected:
      int32_t health() override
      {
        LOG_DBG("AsusCtrlSvc.health");
        return 0;
      };
      int32_t getCurrentActiveGPU() override
      {
        LOG_DBG("AsusCtrlSvc.getCurrentActiveGPU");
        return 0;
      }
      void toggleActiveGPU() override
      {
        LOG_DBG("AsusCtrlSvc.changeActiveGPU");
      }
    };
  } // namespace skynet
} // namespace org

#endif