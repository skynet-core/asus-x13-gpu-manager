project(x13_egpu_service)

file(GLOB SOURCES *.cpp)



add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} service_gen systemd_gen)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE 
    fmt::fmt 
    sdbus-cpp::sdbus-cpp
    egpu_x13_lib::egpu_x13_lib)