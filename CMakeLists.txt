cmake_minimum_required(VERSION 3.9)
project(remeshing_project)
set(CMAKE_CXX_STANDARD 17)

if(MINGW OR CYGWIN)
    add_definitions(-O3)
endif()


add_definitions(-DCGAL_DIR=$ENV{CGAL_DIR})
#add_definitions(-DCGAL_LINKED_WITH_TBB)
#add_definitions(-DCGAL_USE_GMP)
#add_definitions(-DCGAL_USE_MPFR)
#add_definitions(-DCGAL_USE_ZLIB)

link_libraries(../external/glew_2_1_0/lib/Release/Win32/glew32s)
link_libraries(../external/glfw/lib-vc2015/glfw3)
link_libraries(../external/openGL/OPENGL32)
link_libraries(../external/openGL/glut32)
link_libraries(../external/openGL/glu32)
link_libraries($ENV{CGAL_DIR}/build/lib/Debug/CGAL-vc140-mt-gd-4.12.lib)


#Header Locations
set(HEADER_DIRS external/tinyply
        external/libigl/include/
        external/glfw/include/
        external/eigen-git-mirror/
        external/glew_2_1_0/include/
        external/nanoflann/
        external/spectra/
        external/halfedge/
        external/
        $ENV{CGAL_DIR}/include/
        $ENV{CGAL_DIR}/build/include/
        $ENV{BOOST_INCLUDEDIR}/)


add_executable(Remesher src/main.cpp
                external/halfedge/trimesh.cpp
                src/meshMetrics.cpp
                src/meshMetrics.h
                src/remeshingTools.cpp
                src/remeshingTools.h
                src/dataStructures.h
                src/delaunayTriangulation.cpp
                src/delaunayTriangulation.h)
target_include_directories(Remesher PRIVATE ${HEADER_DIRS})



