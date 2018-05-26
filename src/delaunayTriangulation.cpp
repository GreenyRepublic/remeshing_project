//
// Created by maria on 21/05/2018.
//

#include "delaunayTriangulation.h"

void delaunayTriangulation(MeshData& inMesh){

    /*
     * We first need to get the vertices from the parameterisation
     * and convert them to variables of type Point.
    */
    std::vector<Point> pts(inMesh.parameterisedVerts.rows());
    eigenToDelaunay(inMesh.parameterisedVerts, pts);
    //  std::cout << "Size: " << pts.size() << std::endl;
    /*
     * Once we have the points, we create a Delaunay triangulation
     * and insert the points in it.
     */
    Triangulation dt;
    dt.insert(pts.begin(), pts.end());

    /*
     * We now need to get the faces back to be able to render
     * the new triangulation on the 2D parameterisation.
     *
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


bool eigenToDelaunay(Eigen::MatrixXd& inVerts, std::vector<Point>& outPoints){
    for(int row= 0; row < inVerts.rows(); row++){

        outPoints[row] = Point(inVerts(row, 0), inVerts(row, 1));

    }
    return true;

}

/*
bool delaunayToEigen(Triangulation& in, Eigen::MatrixXi& outFaces)
{
    //outVerts.resize(Triangulation.number_of_vertices(), 2);

    int i = 0;
    for (auto vertIterator = Triangulation.all_vertices_begin();
            vertIterator != Triangulation.all_vertices_end();
            vertIterator++)
    {
        outVerts.row(i)(0) = vertIterator->point()->first;
        outVerts.row(i)(1) = vertIterator->point()->second;
        i++;
    }
    return true;
}
 */
