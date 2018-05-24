//
// Created by maria on 21/05/2018.
//

#include "delaunayTriangulation.h"

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Delaunay_triangulation_2<K> Triangulation;
typedef Triangulation::Point Point;
typedef Triangulation::Finite_vertices_iterator Vertices_iterator;
typedef Triangulation::Finite_faces_iterator Faces_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Face_handle Face_handle;

void delaunayTriangulation(MeshData& inMesh){

    /*
     * We first need to get the vertices from the parameterisation
     * and convert them to variables of type Point.
    */
    //std::vector<Point> pts;
    /*
     * Once we have the points, we create a Delaunay triangulation
     * and insert the points in it.
     */
    Triangulation dt;
    //dt.insert(pts.begin(), pts.end());

    /*
     * We now need to get the faces back to be able to render
     * the new triangulation on the 2D parameterisation.
     * To do this we use a Finite_vertices_iterator and then a Finite_cells_iterator
     *
     */
    /*
    Vertices_iterator v_it;
    std::map<Vertex_handle, int> vertices;
    int index = 0;
    for(v_it = dt.finite_vertices_begin(); v_it!= dt.finite_vertices_end(); v_it++){
        vertices[v_it] = index;
        index++;
    }

    //Iterate the faces
    std::map<Face_handle, int> Faces;
    std::map<Face_handle, std::list<int>> Faces_test;
    int index_aux = 0;
    Faces_iterator f_it;

    for(f_it = dt.finite_faces_begin(); f_it!= dt.finite_faces_end(); ++v_it){
        int v0ind = vertices.find(f_it->vertex(0)->point())->second;
        int v1ind = vertices.find(f_it->vertex(1)->point())->second;
        int v2ind = vertices.find(f_it->vertex(2)->point())->second;
    }
     */


}