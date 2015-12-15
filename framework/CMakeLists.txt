set (PIRIS_DATA
chsprintf
pbutton
pcolor
pfont
pcheckbox
pkeyevent
plabel
pmaster
pportingabstract
pscreen
pspecialspinbox
ptouchevent
pwidget
qdebugprint
)

set (PIRIS_SOURCES
fonts/sans16.c
fonts/terminus12.c
fonts/terminus16.c
)

set (PIRIS_HEADERS
passert.h
ptypes.h
)

foreach(P ${PIRIS_DATA})
list (APPEND PIRIS_SOURCES "${P}.cpp" )
list (APPEND PIRIS_HEADERS "${P}.h")

endforeach()

message("${PIRIS_HEADERS}")


add_library (piris OBJECT ${PIRIS_SOURCES} ${PIRIS_HEADERS})
target_include_directories(user_code PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

