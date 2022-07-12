project(x13_egpu_service)

execute_process(
  COMMAND conan install .. --build=missing -s build_type=Debug -pr:b=default
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/cmake
  RESULT_VARIABLE CONAN_SERVER_RESULT)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")

  find_package(fmt CONFIG REQUIRED)
  find_package(sdbus-cpp CONFIG REQUIRED)
  find_package(kmod CONFIG REQUIRED)

  add_custom_target(
    server_gen
    COMMAND
      sdbus-c++-xml2cpp
      ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/interface.xml
      --adaptor=${CMAKE_CURRENT_LIST_DIR}/asus-manager-adapter-glue.h
    SOURCES ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/interface.xml)

  file(GLOB SOURCES *.cpp)
  add_executable(${PROJECT_NAME} ${SOURCES})
  add_dependencies(${PROJECT_NAME} server_gen)
  target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
  target_link_libraries(
    ${PROJECT_NAME} PRIVATE fmt::fmt sdbus-cpp::sdbus-cpp
                            egpu_x13_lib::egpu_x13_lib)
else()
    message(FATAL_ERROR "first install service dependencies")
endif()
