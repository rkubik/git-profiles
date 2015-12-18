add_definitions( -Wall -O0 -ggdb -fPIC )

find_package( Qt4 REQUIRED )
include( ${QT_USE_FILE} )
add_definitions( ${QT_DEFINITIONS} )

include_directories(
    .
    /usr/include/qt4
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_BINARY_DIR}
)

set( SOURCES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/window.cpp
)

set ( MOC_HEADERS
    ${PROJECT_SOURCE_DIR}/src/window.h
)

set ( UIS )

set ( RESOURCES
 ${PROJECT_SOURCE_DIR}/git-profiles.qrc
)

QT4_ADD_RESOURCES( RES_SOURCES ${RESOURCES} )
QT4_WRAP_UI( UI_HEADERS ${UIS} )
QT4_WRAP_CPP( MOC_SRCS ${MOC_HEADERS} )

add_executable( git-profiles ${SOURCES}
                             ${MOC_SRCS}
                             ${RES_SOURCES}
                             ${UI_HEADERS} )

target_link_libraries( git-profiles ${QT_LIBRARIES} )

install( TARGETS git-profiles RUNTIME DESTINATION usr/bin )
