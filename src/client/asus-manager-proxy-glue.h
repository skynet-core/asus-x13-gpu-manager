
/*
 * This file was automatically generated by sdbus-c++-xml2cpp; DO NOT EDIT!
 */

#ifndef __sdbuscpp___home_skynet_Dev_tools_egpu_x13_src_client_asus_manager_proxy_glue_h__proxy__H__
#define __sdbuscpp___home_skynet_Dev_tools_egpu_x13_src_client_asus_manager_proxy_glue_h__proxy__H__

#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <tuple>

namespace org {
namespace skynet {
namespace asus {

class Manager_proxy
{
public:
    static constexpr const char* INTERFACE_NAME = "org.skynet.asus.Manager";

protected:
    Manager_proxy(sdbus::IProxy& proxy)
        : proxy_(proxy)
    {
        proxy_.uponSignal("txStart").onInterface(INTERFACE_NAME).call([this](const std::string& id, const std::string& info){ this->onTxStart(id, info); });
        proxy_.uponSignal("txEnd").onInterface(INTERFACE_NAME).call([this](const std::string& id, const int32_t& code, const std::string& status){ this->onTxEnd(id, code, status); });
    }

    ~Manager_proxy() = default;

    virtual void onTxStart(const std::string& id, const std::string& info) = 0;
    virtual void onTxEnd(const std::string& id, const int32_t& code, const std::string& status) = 0;

public:
    std::tuple<int32_t, std::string> getCurrentMode()
    {
        std::tuple<int32_t, std::string> result;
        proxy_.callMethod("getCurrentMode").onInterface(INTERFACE_NAME).storeResultsTo(result);
        return result;
    }

    std::tuple<int32_t, std::string> setIntegrated()
    {
        std::tuple<int32_t, std::string> result;
        proxy_.callMethod("setIntegrated").onInterface(INTERFACE_NAME).storeResultsTo(result);
        return result;
    }

    std::tuple<int32_t, std::string> setHybrid()
    {
        std::tuple<int32_t, std::string> result;
        proxy_.callMethod("setHybrid").onInterface(INTERFACE_NAME).storeResultsTo(result);
        return result;
    }

    std::tuple<int32_t, std::string> setXMobile()
    {
        std::tuple<int32_t, std::string> result;
        proxy_.callMethod("setXMobile").onInterface(INTERFACE_NAME).storeResultsTo(result);
        return result;
    }

    std::tuple<int32_t, std::string> setCompute()
    {
        std::tuple<int32_t, std::string> result;
        proxy_.callMethod("setCompute").onInterface(INTERFACE_NAME).storeResultsTo(result);
        return result;
    }

private:
    sdbus::IProxy& proxy_;
};

}}} // namespaces

#endif
