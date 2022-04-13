cmake_minimum_required(VERSION 3.21.2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set (PROJECT_SOURCE_DECLARATION_DIRECTORY ${PROJECT_SOURCE_DIR}/update_service/include)
set (PROJECT_SOURCE_DEFINITION_DIRECTORY ${PROJECT_SOURCE_DIR}/update_service/src)
set (MAIN_FILE ${PROJECT_SOURCE_DEFINITION_DIRECTORY}/main.cpp)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)



set(Boost_ROOT ${BOOST_ROOT})
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME ON) 
find_package(Boost 1.79.0 REQUIRED) 

if(Boost_FOUND)
    message(STATUS "Boost version: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories (${PROJECT_SOURCE_DECLARATION_DIRECTORY})
    add_library(UpdateService STATIC ${MAIN_FILE})
    target_link_libraries(UpdateService ${BOOST_LIBRARIES})
endif()
 

