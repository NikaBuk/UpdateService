project(main_app)

add_executable(main_app
               src/main.cpp
               )
include_directories(${CMAKE_SOURCE_DIR}/update_service/src)
target_link_libraries(main_app update_service_lib)