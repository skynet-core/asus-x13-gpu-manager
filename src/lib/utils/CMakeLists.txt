project(gpu_switch VERSION 0.1.0)

file(GLOB SRCS *.cpp *.h)

add_executable(${PROJECT_NAME} ${SRCS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../)
target_link_libraries(${PROJECT_NAME} PUBLIC asus-gpu-lib::asus-gpu-lib)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)