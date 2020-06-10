set (APP app)

set (SomethingLIB Something)

file(GLOB ${APP}_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/src/${APP} *.c;*.cpp;*.txt)
file(GLOB ${APP}_HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/src/${APP} *.h;../inc/*.h)

foreach(PATH ${PROJECT_INCLUDES})
	include_directories(${PATH})
endforeach(PATH)

add_executable(${APP} ${${APP}_SOURCES} ${${APP}_HEADERS})

target_link_libraries(${APP} ${LIB} ${TestLIB} ${OS_LIBS})

if (WITH_CPPCHECKTARGET)
	file(GLOB to_remove RELATIVE ${CMAKE_SOURCE_DIR}/src/${APP} *.txt)
	list(REMOVE_ITEM ${APP}_SOURCES ${to_remove})
	include (GenerateCppcheck)
	GENERATE_CPPCHECK(SOURCES ${${APP}_SOURCES} TARGET_NAME "CppCheck_${APP}" INCLUDES ${PROJECT_INCLUDES})
endif(WITH_CPPCHECKTARGET)

