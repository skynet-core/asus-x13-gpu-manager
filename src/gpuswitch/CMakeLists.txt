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
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ WORLD_READ
  DESTINATION bin)

install(
    FILES ../../share/systemd/${PROJECT_NAME}.service
    CONFIGURATIONS Release
    PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
    DESTINATION /etc/systemd/system/)
