project(x13_egpu_client)


file(GLOB SOURCES *.cpp)


add_executable(${PROJECT_NAME} ${SOURCES})
add_dependencies(${PROJECT_NAME} service_gen)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE 
    fmt::fmt 
    sdbus-cpp::sdbus-cpp
    egpu_x13_lib::egpu_x13_lib
    )