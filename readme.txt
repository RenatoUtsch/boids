Computer Graphics - Practical Exercise 2 Documentation
Boids
2014/02
Author: Renato Utsch Gonçalves

== Compiling
=============
To compile the practical exercise, you must use CMake.
Follow the steps as below:
1. Enter the project's root (the folder with this file).
2. Create a folder called "build".
3. Use the terminal to go to the "build" folder.
4. Type "cmake .." and press enter.
5. Type "make" and press enter.

An executable with name boids will be created and will
be able to be executed with "./boids".

The dependencies are on CMake, on a C++ compiler, on glfw's
dependencies (on ubuntu, they have the name "xorg-dev" and
"libglu1-mesa-dev") and on OpenGL.

The compilation of this program was tested in Linux
(ArchLinux and Ubuntu), OS X (OS X Yosemite) and Windows
(Windows 7 and 8.1).

To compile on linux, it is necessary to install the
libraries that GLFW depends on to compile.

