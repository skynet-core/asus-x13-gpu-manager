project(egpu_x13_lib VERSION 0.1.0)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
include(CTest)
include(CPack)

file(GLOB LIB_SRC *.cpp *.h)

add_library(${PROJECT_NAME} ${LIB_SRC})
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
                         $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

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

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN *.h)
