cmake_minimum_required (VERSION 3.1)

# Name of the project
project (filter)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
set(CMAKE_MODULE_PATH "${CMAKE_CXX_FLAGS}" "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(TinyXML2 REQUIRED)

###################################################################################################
# Header Files
###################################################################################################
set (SOURCE_H
    src/color.h
    src/parse_xml.h
    src/search_item.h
)

###################################################################################################
#  Source Files
###################################################################################################
set (SOURCE_CPP
   src/main.cpp
   src/parse_xml.cpp
   src/color.cpp
)

add_executable(filter ${SOURCE_CPP} ${SOURCE_H})
target_include_directories(filter PRIVATE ${TinyXML2_INCLUDE_DIRS})
target_link_libraries(filter ${TinyXML2_LIBRARIES})

install(TARGETS filter DESTINATION bin)
