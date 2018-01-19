cmake_minimum_required( VERSION 2.8 )

project( git-profiles )

set( CMAKE_INSTALL_PREFIX "/" )

set( PACKAGE_MAJOR 0 )
set( PACKAGE_MINOR 2 )
set( PACKAGE_PATCH 2 )

message( "MAJOR: ${PACKAGE_MAJOR}" )
message( "MINOR: ${PACKAGE_MINOR}" )
message( "PATCH: ${PACKAGE_PATCH}" )

add_subdirectory( bin )

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)
