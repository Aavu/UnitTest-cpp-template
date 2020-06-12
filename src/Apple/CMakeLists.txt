set(CurrLib Apple)

# add include directories
foreach(PATH ${PROJECT_INCLUDES})
    include_directories(${PATH})
endforeach(PATH)

# build a static library
add_library(${CurrLib} STATIC Apple.cpp ../../inc/Apple.h)
set_target_properties(${CurrLib} PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# set output name
set_target_properties(${CurrLib} PROPERTIES OUTPUT_NAME "${CurrLib}")
set_target_properties(${CurrLib} PROPERTIES PREFIX "lib")