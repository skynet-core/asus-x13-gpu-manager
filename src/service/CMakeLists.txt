project(asus-gpu-service)

execute_process(
  COMMAND conan install .. --build=missing -s build_type=${CMAKE_BUILD_TYPE}
          -pr:b=default
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/cmake
  RESULT_VARIABLE CONAN_SERVER_RESULT)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")

  find_package(sdbus-cpp CONFIG REQUIRED)

  add_custom_target(
    service_gen
    COMMAND
      sdbus-c++-xml2cpp
      ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/interface.xml
      --adaptor=${CMAKE_CURRENT_LIST_DIR}/asus-manager-adapter-glue.h
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/interface.xml)

  add_custom_target(
    systemd_gen
    COMMAND
      sdbus-c++-xml2cpp
      ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/systemd.xml
      --proxy=${CMAKE_CURRENT_LIST_DIR}/systemd-manager-proxy-glue.h
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/systemd.xml)

  file(GLOB SOURCES *.cpp)
  add_executable(${PROJECT_NAME} ${SOURCES})
  add_dependencies(${PROJECT_NAME} service_gen systemd_gen)
  target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
  target_link_libraries(${PROJECT_NAME} PRIVATE sdbus-cpp::sdbus-cpp
                                                asus-gpu-lib::asus-gpu-lib)

  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
    CONFIGURATIONS Release
    PERMISSIONS OWNER_EXECUTE
    DESTINATION bin)

else()
  message(FATAL_ERROR "first install service dependencies")
endif()
