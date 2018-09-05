cmake_minimum_required(VERSION 3.12)
project(NEATExample)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCES
        *.h
        *.cpp
        )

add_executable(SFMLBook ${SOURCES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(SFMLBook ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

set(CMAKE_MODULE_PATH "/usr/share/SFML/cmake/Modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED audio network graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SFMLBook ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()