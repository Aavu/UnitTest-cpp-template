set (APP app)

set (SomethingLIB Something)
set (AppleLIB Apple)

file(GLOB ${APP}_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/src/${APP} *.c;*.cpp;*.txt)
file(GLOB ${APP}_HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/src/${APP} *.h;../inc/*.h)

foreach(PATH ${PROJECT_INCLUDES})
	include_directories(${PATH})
endforeach(PATH)

add_executable(${APP} ${${APP}_SOURCES} ${${APP}_HEADERS})

target_link_libraries(${APP} ${LIB} ${TestLIB})

