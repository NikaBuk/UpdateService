
cmake_minimum_required( VERSION 3.20 )

project( update_service_lib )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED True )

file( GLOB_RECURSE SRC_FILES
      "*.h"
      "*.cpp"
      )

set( CMAKE_CXX_FLAGS "-Wall -Wextra" )
set( CMAKE_CXX_FLAGS_DEBUG "-g3 -O0" )
set( CMAKE_CXX_FLAGS_RELEASE "-O3" )

add_library( update_service_lib SHARED ${SRC_FILES} )

#TODO: add logging library

set( Boost_ROOT $ENV{BOOST_DIR} )
set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME ON )
find_package( Boost )
if ( Boost_FOUND )
    message( STATUS "Boost version: ${Boost_VERSION}" )
    target_include_directories( update_service_lib PUBLIC ${Boost_INCLUDE_DIRS} )
    target_link_libraries( update_service_lib PUBLIC ${BOOST_LIBRARIES} )
endif ()
 

