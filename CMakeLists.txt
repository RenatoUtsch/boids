##
 # Autor: Renato Utsch Gonçalves
 # Ciência da Computação, UFMG
 # Computação Gráfica
 # Trabalho Prático 2 - Boids
 #
 # Copyright (c) 2014 Renato Utsch
 #
 # Permission is hereby granted, free of charge, to any person obtaining a copy
 # of this software and associated documentation files (the "Software"), to deal
 # in the Software without restriction, including without limitation the rights
 # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 # copies of the Software, and to permit persons to whom the Software is
 # furnished to do so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included in
 # all copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 # THE SOFTWARE.
 ##

# CMakeLists.txt file for compiling the project with CMake.

# Basic configuration
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )
project( boids C CXX )

set( BOIDS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( BOIDS_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

set( BOIDS_DEFINITIONS "" )
set( BOIDS_INCLUDE_DIRS "" )
set( BOIDS_LIBRARIES "" )

# Add gcc options
if( UNIX )
    set( BOIDS_DEFINITIONS
        "${BOIDS_DEFINITIONS} -Wall -Wextra -Werror -Wno-deprecated-declarations -Wno-unused-parameter -Wno-comment -g3 -pg" )
endif()

# Add catch for unit testing.
set( BOIDS_INCLUDE_DIRS ${BOIDS_INCLUDE_DIRS} "${BOIDS_SOURCE_DIR}/3rdparty/catch/include" )

# Find PKGCONFIG for GLFW.
find_package( PkgConfig )
if( NOT PkgConfig_FOUND )
    set( COMPILE_GLFW TRUE )
endif()
# Find GLFW.
if( NOT COMPILE_GLFW )
    pkg_search_module( GLFW glfw3 )
endif()
if( GLFW_FOUND )
    set( BOIDS_INCLUDE_DIRS ${BOIDS_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS} )
    set( BOIDS_LIBRARIES ${BOIDS_LIBRARIES} ${OPENGL_glu_LIBRARY} ${GLFW_STATIC_LIBRARIES} )
endif()

if( COMPILE_GLFW OR NOT GLFW_FOUND )
    # Include glfw
    message( STATUS "GLFW Not Found - Compiling GLFW from source..." )
    set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "no examples" )
    set( GLFW_BUILD_TESTS OFF CACHE BOOL "no tests" )
    set( GLFW_BUILD_DOCS OFF CACHE BOOL "no docs" )
    set( GLFW_INSTALL OFF CACHE BOOL "no installation" )
    add_subdirectory( "${BOIDS_SOURCE_DIR}/3rdparty/glfw" )
    set( BOIDS_INCLUDE_DIRS ${BOIDS_INCLUDE_DIRS} "${BOIDS_SOURCE_DIR}/3rdparty/glfw/include" )
    set( BOIDS_LIBRARIES ${BOIDS_LIBRARIES} glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES} )
endif()

# Boids sources
set( BOIDS_SOURCE_FILES "${BOIDS_SOURCE_DIR}/source/Engine.cpp"
                        "${BOIDS_SOURCE_DIR}/source/main.cpp"
                        "${BOIDS_SOURCE_DIR}/source/state/StateFactory.cpp"
                        "${BOIDS_SOURCE_DIR}/source/system/AnimationSystem.cpp"
                        "${BOIDS_SOURCE_DIR}/source/system/CameraSystem.cpp"
                        "${BOIDS_SOURCE_DIR}/source/system/CollisionSystem.cpp"
                        "${BOIDS_SOURCE_DIR}/source/system/MovementSystem.cpp"
                        "${BOIDS_SOURCE_DIR}/source/system/RenderSystem.cpp"
                        "${BOIDS_SOURCE_DIR}/source/util/draw.cpp"
                        "${BOIDS_SOURCE_DIR}/source/util/sleep.cpp" )

# Compile
add_definitions( ${BOIDS_DEFINITIONS} )
include_directories( ${BOIDS_INCLUDE_DIRS} )

add_executable( boids ${BOIDS_SOURCE_FILES} )
target_link_libraries( boids ${BOIDS_LIBRARIES} )
