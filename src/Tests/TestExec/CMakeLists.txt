set (APP TestExec)

set (TestLIB UnitTest++)

set (SomethingLIB Something)
set(AppleLIB Apple)

##############################################################
## unitTest++
file(GLOB ${TestLIB}_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/src/Tests/${APP} ../../../3rdparty/unittest-cpp-master/${TestLIB}/${PlatformDir}/*.c;../../../3rdparty/unittest-cpp-master/${TestLIB}/${PlatformDir}/*.cpp)
file(GLOB ${TestLIB}_HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/src/Tests/${APP} ../../../3rdparty/unittest-cpp-master/${TestLIB}/${PlatformDir}/*.h)

set(PlatformDir Posix)
file(GLOB ${TestLIB}_SOURCES_2 RELATIVE ${CMAKE_SOURCE_DIR}/src/Tests/${APP} ../../../3rdparty/unittest-cpp-master/${TestLIB}/${PlatformDir}/*.cpp)
file(GLOB ${TestLIB}_HEADERS_2 RELATIVE ${CMAKE_SOURCE_DIR}/src/Tests/${APP} ../../../3rdparty/unittest-cpp-master/${TestLIB}/${PlatformDir}/${PlatformDir}/*.h)
list (APPEND PROJECT_INCLUDES ${CMAKE_SOURCE_DIR}/3rdparty/unittest-cpp-master/${TestLIB})

# build a static library
if (WITH_TESTS)
    add_library(${TestLIB} STATIC ${${TestLIB}_SOURCES} ${${TestLIB}_HEADERS} ${${TestLIB}_SOURCES_2} ${${TestLIB}_HEADERS_2})
    set_target_properties(${TestLIB} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

    set_target_properties(${TestLIB} PROPERTIES OUTPUT_NAME "${TestLIB}")
    set_target_properties(${TestLIB} PROPERTIES PREFIX "lib")

    set_target_properties(${TestLIB} PROPERTIES COMPILE_FLAGS "-w")

endif (WITH_TESTS)

##############################################################
## TestExec
file(GLOB ${APP}_SOURCES RELATIVE ${CMAKE_SOURCE_DIR}/src/Tests/${APP} Test.cpp)
file(GLOB ${APP}_HEADERS RELATIVE ${CMAKE_SOURCE_DIR}/src/Tests/${APP} *.h;../incl/*.h)
source_group (Main FILES ${APP}_SOURCES ${APP}_HEADERS)

# these are the individual tests
file(GLOB ${APP}_SOURCES_TEST RELATIVE ${CMAKE_SOURCE_DIR}/src/Tests/${APP} ../Tests/*.cpp;)
file(GLOB ${APP}_HEADERS_TEST RELATIVE ${CMAKE_SOURCE_DIR}/src/Tests/${APP} ../Tests/*.h)
source_group (Tests FILES ${APP}_SOURCES_TEST ${APP}_HEADERS_TEST)

# add include directories
foreach(PATH ${PROJECT_INCLUDES})
    include_directories(${PATH})
endforeach(PATH)

if (WITH_TESTS)
    add_executable(${APP} ${${APP}_SOURCES} ${${APP}_HEADERS} ${${APP}_SOURCES_TEST} ${${APP}_HEADERS_TEST})

    # link the libraries
    target_link_libraries(${APP} ${LIB} ${TestLIB} ${SomethingLIB} ${AppleLIB})
endif (WITH_TESTS)


