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

find_package( Qt5Widgets )
find_package( Qt5Svg )

QT5_ADD_RESOURCES( UI_RESOURCES ${RESOURCES} )
include_directories( ${Qt5Widgets_INCLUDE_DIRS} )
add_definitions( ${Qt5Widgets_DEFINITIONS} )
add_executable( git-profiles ${SOURCES} ${HEADERS} ${UI_RESOURCES} )
target_link_libraries( git-profiles Qt5::Widgets Qt5::Svg )

install( TARGETS git-profiles RUNTIME DESTINATION usr/bin )
