add_definitions( -Wall -O0 -ggdb -fPIE )

set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_INCLUDE_CURRENT_DIR ON )

include_directories(
    .
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
)

set( SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/window.cpp
)

set( HEADERS
    ${PROJECT_SOURCE_DIR}/src/window.h
)

set( RESOURCES ${PROJECT_SOURCE_DIR}/git-profiles.qrc )

find_package( Qt5Widgets QUIET )
find_package( Qt5Svg QUIET )
find_package( Qt4 QUIET )

if( Qt5Widgets_FOUND AND Qt5Svg_FOUND )
    message( "Building with QT5" )
    set( QT 5 PARENT_SCOPE )
    QT5_ADD_RESOURCES( UI_RESOURCES ${RESOURCES} )
    include_directories( ${Qt5Widgets_INCLUDE_DIRS} )
    add_definitions( ${Qt5Widgets_DEFINITIONS} )
    add_executable( git-profiles ${SOURCES} ${HEADERS} ${UI_RESOURCES} )
    target_link_libraries( git-profiles Qt5::Widgets Qt5::Svg )
elseif( Qt4_FOUND )
    message( "Building with QT4" )
    set( QT 4 PARENT_SCOPE )
    INCLUDE( ${QT_USE_FILE} )
    include_directories( ${QT_INCLUDES} )
    QT4_ADD_RESOURCES( UI_RESOURCES ${RESOURCES} )
    add_executable( git-profiles ${SOURCES} ${UI_RESOURCES} )
    target_link_libraries( git-profiles ${QT_LIBRARIES} )
else()
    message( FATAL_ERROR "Failed to find Qt 4 or 5 on the system. CMake will exit." )
endif()

install( TARGETS git-profiles RUNTIME DESTINATION usr/bin )
