cmake_minimum_required(VERSION 3.9)
project(remeshing_project)
set(CMAKE_CXX_STANDARD 17)

add_definitions(-DCGAL_DIR=$ENV{CGAL_DIR})

link_libraries(../external/glew_2_1_0/lib/Release/Win32/glew32s)
link_libraries(../external/glfw/lib-vc2015/glfw3)
link_libraries(../external/openGL/OPENGL32)
link_libraries(../external/openGL/glut32)
link_libraries(../external/openGL/glu32)
link_libraries($ENV{CGAL_DIR}/build/lib/CGAL-vc140-mt-gd-4.12.lib)
link_libraries($ENV{CGAL_DIR}/auxiliary/gmp/lib/libgmp-10.lib)
link_libraries($ENV{CGAL_DIR}/auxiliary/gmp/lib/libmpfr-4.lib)

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
        $ENV{CGAL_DIR}/auxiliary/gmp/include
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



