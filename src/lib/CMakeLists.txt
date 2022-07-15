project(asus-gpu-lib VERSION 0.1.0)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(CTest)
include(CPack)
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

execute_process(
  COMMAND conan install .. --build=missing -s build_type=${CMAKE_BUILD_TYPE}
          -pr:b=default
  WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/cmake
  RESULT_VARIABLE CONAN_SERVER_RESULT)

if(EXISTS "${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")
  include("${CMAKE_CURRENT_LIST_DIR}/cmake/conan_toolchain.cmake")

  find_package(fmt CONFIG REQUIRED)
  find_package(libsystemd CONFIG REQUIRED)
  find_package(kmod CONFIG REQUIRED)
  find_package(Threads)
  find_package(spdlog CONFIG REQUIRED)

  configure_file(${CMAKE_CURRENT_LIST_DIR}/config/config.h.in
                 ${CMAKE_CURRENT_LIST_DIR}/config/config.h)

  file(GLOB LIB_SRC *.cpp *.h)

  add_library(${PROJECT_NAME} ${LIB_SRC})
  add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

  target_include_directories(
    ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

  target_link_libraries(
    ${PROJECT_NAME} PUBLIC fmt::fmt kmod::kmod spdlog::spdlog libsystemd::libsystemd
                           Threads::Threads)

  target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

  set(MY_DEFINITIONS "")
  if(DEFINED LEVEL_DEBUG)
    list(APPEND MY_DEFINITIONS LEVEL_DEBUG)
  elseif(DEFINED LEVEL_INFO)
    list(APPEND MY_DEFINITIONS LEVEL_INFO)
  elseif(DEFINED LEVEL_WARN)
    list(APPEND MY_DEFINITIONS LEVEL_WARN)
  elseif(DEFINED LEVEL_ERROR)
    list(APPEND MY_DEFINITIONS LEVEL_ERROR)
  endif()
  target_compile_definitions(${PROJECT_NAME} PUBLIC "${MY_DEFINITIONS}")

  configure_package_config_file(
    cmake/config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION "lib/cmake"
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
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/asus-gpu-lib
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING
    PATTERN *.h)

  add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils)
else()
  message(FATAL_ERROR "first install librray dependencies")
endif()
