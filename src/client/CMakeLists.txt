project(asus-gpu-cli)

message(STATUS "CONAN_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

execute_process(
  COMMAND conan install .. --build=missing -s build_type=${CMAKE_BUILD_TYPE}
          -pr:b=default
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/cmake
  RESULT_VARIABLE CONAN_SERVER_RESULT)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")

  file(GLOB SOURCES *.cpp)

  find_package(fmt CONFIG REQUIRED)
  find_package(sdbus-cpp CONFIG REQUIRED)
  find_package(CLI11 CONFIG REQUIRED)

  add_custom_target(
    client_gen
    COMMAND
      sdbus-c++-xml2cpp
      ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/interface.xml
      --proxy=${CMAKE_CURRENT_LIST_DIR}/asus-manager-proxy-glue.h
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/interface.xml)

  add_executable(${PROJECT_NAME} ${SOURCES})
  add_dependencies(${PROJECT_NAME} client_gen)

  target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
  target_include_directories(${PROJECT_NAME}
                             PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(
    ${PROJECT_NAME} PRIVATE fmt::fmt sdbus-cpp::sdbus-cpp
                            asus-gpu-lib::asus-gpu-lib CLI11::CLI11)

  install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
    CONFIGURATIONS Release
    PERMISSIONS WORLD_EXECUTE
    DESTINATION bin
    RENAME client)
else()
  message(FATAL_ERROR "first install client dependencies")
endif()
