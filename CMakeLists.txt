cmake_minimum_required (VERSION 3.0)
project (app)

set(CMAKE_CXX_STANDARD 11)

set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake.modules")

# output directories
# build libraries into /lib and executables into /bin
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY	${CMAKE_SOURCE_DIR}/lib)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/debug)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/debug)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/release)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/release)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/relwithdebinfo)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/relwithdebinfo)

# unsure if these are necessary
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG})
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO})

# set directories
set (PROJECT_DIRECTORIES)
list (APPEND PROJECT_DIRECTORIES ${CMAKE_SOURCE_DIR}/src/app)
list (APPEND PROJECT_DIRECTORIES ${CMAKE_SOURCE_DIR}/src/Tests/TestExec)
    
# set includes
set (PROJECT_INCLUDES)
list (APPEND PROJECT_INCLUDES ${CMAKE_SOURCE_DIR}/inc)       
list (APPEND PROJECT_INCLUDES ${CMAKE_SOURCE_DIR}/src/inc)       
list (APPEND PROJECT_INCLUDES ${CMAKE_BINARY_DIR}/inc)       

# add directories
foreach(PATH ${PROJECT_DIRECTORIES})
    get_filename_component( FILENAME ${PATH} NAME_WE)
    message(STATUS ${FILENAME})
    add_subdirectory(${PATH} "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}")
endforeach(PATH)


# output version number variable
message(STATUS ${PROJECT_NAME} Version: ${PROJECT_VERSION})
message(STATUS "")

# integrate cppcheck targets in IDE
option (WITH_CPPCHECKTARGET "Add target for cppcheck testing" OFF)
#######################################################################################################
# ## tests

# with tests or not
option (WITH_TESTS "Use UnitTest++ for testing" ON)

if (WITH_TESTS)
    enable_testing()
    
    # add tests here
    add_test(Something ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/TestExec Something)

    find_package(Cppcheck)
    if (CPPCHECK_FOUND)
        # copy list just to be sure
        list(APPEND CPPCHK_DEPLIST ${PROJECT_DIRECTORIES})

        # generate include list with "-I" prefix
        foreach(arg ${PROJECT_INCLUDES})
            set(CPPCHK_INCL "${CPPCHK_INCL} -I ${arg}")
        endforeach(arg ${PROJECT_INCLUDES})

        # add the test itself!
        add_test(CppCheck ${CPPCHECK_EXECUTABLE} "--error-exitcode=1" ${CPPCHK_DEPLIST} ${CPPCHK_INCL})
    endif (CPPCHECK_FOUND)
endif (WITH_TESTS)

