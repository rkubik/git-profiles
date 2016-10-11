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

if( QT5 )
    message( "Building with QT5" )
    find_package( Qt5Widgets REQUIRED )
    find_package( Qt5Svg REQUIRED )
    QT5_ADD_RESOURCES( UI_RESOURCES ${RESOURCES} )
    include_directories( ${Qt5Widgets_INCLUDE_DIRS} )
    add_definitions( ${Qt5Widgets_DEFINITIONS} )
    add_executable( git-profiles ${SOURCES} ${HEADERS} ${UI_RESOURCES} )
    target_link_libraries( git-profiles Qt5::Widgets Qt5::Svg )
elseif( QT4 )
    message( "Building with QT4" )
    find_package( Qt4 REQUIRED )
    include_directories( ${QT_INCLUDES} )
    add_executable( git-profiles ${SOURCES} )
    target_link_libraries( git-profiles ${QT_QTCORE_LIBRARY} )    
else()
    message( FATAL_ERROR "Only QT versions 4 and 5 are supported, CMake will exit." )
endif()

install( TARGETS git-profiles RUNTIME DESTINATION usr/bin )
