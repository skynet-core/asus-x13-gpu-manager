project(egpu_x13_lib VERSION 0.1.0)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(CTest)
include(CPack)


execute_process(
  COMMAND conan install .. --build=missing -s build_type=Debug -pr:b=default
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/cmake
  RESULT_VARIABLE CONAN_SERVER_RESULT)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")

find_package(fmt CONFIG REQUIRED)
find_package(sdbus-cpp CONFIG REQUIRED)
find_package(kmod CONFIG REQUIRED)
find_package(Threads)

add_custom_target(
  systemd_gen
  COMMAND
    sdbus-c++-xml2cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/systemd.xml
    --proxy=${CMAKE_CURRENT_LIST_DIR}/systemd-manager-proxy-glue.h
  SOURCES ${CMAKE_CURRENT_LIST_DIR}/../../share/interfaces/systemd.xml)

configure_file(${CMAKE_CURRENT_LIST_DIR}/config/config.h.in
               ${CMAKE_CURRENT_LIST_DIR}/config/config.h)

file(GLOB LIB_SRC *.cpp *.h)

add_library(${PROJECT_NAME} ${LIB_SRC})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
add_dependencies(${PROJECT_NAME} systemd_gen)

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(${PROJECT_NAME} PUBLIC fmt::fmt sdbus-cpp::sdbus-cpp
                                             kmod::kmod Threads::Threads)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

if(DEFINED LEVEL_DEBUG)
  target_compile_definitions(${PROJECT_NAME} PUBLIC LEVEL_DEBUG)
elseif(DEFINED LEVEL_INFO)
  target_compile_definitions(${PROJECT_NAME} PUBLIC LEVEL_INFO)
elseif(DEFINED LEVEL_WARN)
  target_compile_definitions(${PROJECT_NAME} PUBLIC LEVEL_WARN)
elseif(DEFINED LEVEL_ERROR)
  target_compile_definitions(${PROJECT_NAME} PUBLIC LEVEL_ERROR)
endif()

configure_package_config_file(
  cmake/config.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
  INSTALL_DESTINATION "lib/cmake/${PROJECT_NAME}"
  NO_SET_AND_CHECK_MACRO)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}-export
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)

install(
  EXPORT ${PROJECT_NAME}-export
  FILE ${PROJECT_NAME}-targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION "lib/cmake/${PROJECT_NAME}")

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING
  PATTERN *.h)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils)
else()
  message(FATAL_ERROR "first install librray dependencies")
endif()
