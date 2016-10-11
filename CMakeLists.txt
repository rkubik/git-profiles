cmake_minimum_required( VERSION 3.0.0 FATAL_ERROR )

project( git-profiles )

set( CMAKE_INSTALL_PREFIX "/" )

set( PACKAGE_MAJOR 0 )
set( PACKAGE_MINOR 1 )
set( PACKAGE_PATCH 0 )

message( "MAJOR: ${PACKAGE_MAJOR}" )
message( "MINOR: ${PACKAGE_MINOR}" )
message( "PATCH: ${PACKAGE_PATCH}" )

option( QT5 "Compile with QT5" OFF )
option( QT4 "Compile with QT4" OFF )

if( NOT(QT5 OR QT4) )
    set( QT5 ON )
endif()

configure_file(
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

add_subdirectory( bin )
