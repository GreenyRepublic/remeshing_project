cmake_minimum_required(VERSION 3.10)
project(remeshing_project)
set(CMAKE_CXX_STANDARD 17)

if(MINGW OR CYGWIN)
    add_definitions(-O3)
endif()

link_libraries(../external/glew_2_1_0/lib/Release/Win32/glew32s)
link_libraries(../external/glfw/lib-vc2015/glfw3)

link_libraries(../external/openGL/OPENGL32)
link_libraries(../external/openGL/glut32)
link_libraries(../external/openGL/glu32)


#Header Locations
set(HEADER_DIRS external/tinyply
        external/libigl/include/
        external/glfw/include/
        external/eigen-git-mirror/
        external/glew_2_1_0/include/
        external/nanoflann/
        external/misc/
        external/spectra/
        external/halfedge/
         src/)

add_executable(Remesher src/main.cpp external/halfedge/trimesh.cpp src/meshMetrics.cpp src/meshMetrics.h)
target_include_directories(Remesher PRIVATE ${HEADER_DIRS})




