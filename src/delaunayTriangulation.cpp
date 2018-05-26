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
    Eigen::MatrixXi delaunayFaces;
    //this is me trying to debug
    printf("Hello");
    delaunayToEigen(dt, delaunayFaces);
    inMesh.meshFaces = delaunayFaces;


}

void lloydRelaxation(Triangulation& inTri, Eigen::MatrixXd& outVerts, int iterations)
{
    for (int i = 0; i < iterations; i++) {
        int j = 0;
        //Construct voronoi cell for each vertex, then shift it to that cell's centroid
        for (auto iter = inTri.all_vertices_begin();
             iter != inTri.all_vertices_end();
             iter++) {
            //Construct polygon from circumcircle centers of incident polygons
            Point centroid(0.0, 0.0);
            int count = 0;
            for (auto face : iter->incident_faces()) {
                centroid += inTri.dual(face);
                count++;
            }
            iter->set_point(centroid / count);
            outVerts.row(j)[0] = iter->point().first;
            outVerts.row(j)[1] = iter->point().second;
            j++;
        }
    }
}

bool eigenToDelaunay(Eigen::MatrixXd& inVerts, std::vector<Point>& outPoints){
    for(int row= 0; row < inVerts.rows(); row++){

        outPoints[row] = Point(inVerts(row, 0), inVerts(row, 1));

    }
    return true;

}

bool delaunayToEigen(Triangulation& in, Eigen::MatrixXi& outFaces){
    int index = 0;
    Vertices_iterator v_it;
    Faces_iterator f_it;

    for(v_it= in.finite_vertices_begin(); v_it < in.finite_vertices_end(); ++v_it){
        v_it->info() =index++;
    }

    int size = 0;

    //I don't know how to get the number of faces in the delaunay triangulation
    for(f_it = in.finite_faces_begin(); f_it < in.finite_faces_end(); ++f_it){
        size++;
    }

    outFaces.resize(size, 3);
    int row= 0;
    for(f_it = in.finite_faces_begin(); f_it < in.finite_faces_end(); ++f_it){
        outFaces(row, 0) = f_it->vertex(0)->info();
        outFaces(row, 1) = f_it->vertex(1)->info();
        outFaces(row, 2) = f_it->vertex(2)->info();
        row++;
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
