project(asus-gpu-switch)

file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE asus-gpu-lib::asus-gpu-lib)

install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
  CONFIGURATIONS Release
  PERMISSIONS OWNER_EXECUTE
  DESTINATION bin)
