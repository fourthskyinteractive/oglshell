# OpenGL Shell - OOP wrapper for use in C++ programs. #

### What is OpenGL Shell? ###

OpenGL Shell is an open source and cross-platform OOP-based wrapper around OpenGL and NVIDIA Cg C-based APIs. The goal of wrapper is to provide abstraction over numerous GL calls, window-system differences and GLSL/Cg shaders. Also with shell it is possible to write managed code, using smart pointers to avoid memory leaks, which is impossible with "pure" OpenGL.

### What platforms are supported? ###

Currently library works under Windows XP/Vista and Linux. I've made some efforts to make source code portable, now it is compiled in MSC and GCC. In future MinGW may be supported too, if needed.