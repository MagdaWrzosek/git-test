# Cmake setup - How to add new subproject
In top level CMakeLists.txt new subproject can be added with `add_subdirectory(<directory name>)`
Subproject CMakeLists.txt(<projName/CMakeLists.txt) can contain any arbitrary set up.
The simplest one is just new target with one file. 
This can be achieved with `add_executable(<target name> <file1.cpp> <file2.cpp>...)` 

