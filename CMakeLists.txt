cmake_minimum_required(VERSION 3.18)

project(
  asus-gpu-manager
  VERSION 0.1.0
  LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(LEVEL_DEBUG
    ON
    CACHE STRING "log_level" FORCE)
set(SYS_LOG_ENABLED
    ON
    CACHE STRING "sys_log_enabled" FORCE)

set(CMAKE_INSTALL_PREFIX
    /opt/asus-gpu-man
    CACHE STRING "install_prefix" FORCE)

add_subdirectory(src/lib)
add_subdirectory(src/service)
add_subdirectory(src/client)

install(
  FILES share/systemd/asus-gpu-man.service
  CONFIGURATIONS Release
  PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
  DESTINATION /etc/system.d/system/)

install(
  FILES share/dbus-1/system.d/org.skynet.asus.conf
  CONFIGURATIONS Release
  PERMISSIONS OWNER_WRITE OWNER_READ GROUP_READ WORLD_READ
  DESTINATION /etc/dbus-1/system.d/)

install(
  FILES unistall.sh
  CONFIGURATIONS Release
  PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
  RENAME unistall
  DESTINATION bin)
