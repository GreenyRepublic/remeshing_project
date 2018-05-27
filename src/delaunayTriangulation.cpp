//
// Created by maria on 21/05/2018.
//

#include "delaunayTriangulation.h"

void delaunayTriangulation(MeshData& inMesh){

    /*
     * We first need to get the vertices from the parameterisation
     * and convert them to variables of type Point.
    */
    std::vector<std::pair<Point, size_t>> pts;

    for(int row= 0; row < inMesh.parameterisedVerts.rows(); row++){

        pts.push_back(std::make_pair(Point(inMesh.parameterisedVerts(row, 0),
                                           inMesh.parameterisedVerts(row, 1)),
                                     row));
    }
    //eigenToDelaunay(inMesh.parameterisedVerts, pts);

    //  std::cout << "Size: " << pts.size() << std::endl;
    /*
     * Once we have the points, we create a Delaunay triangulation
     * and insert the points in it.
     */
    Triangulation dt (pts.begin(), pts.end());


    /*
     * We now need to get the faces back to be able to render
     * the new triangulation on the 2D parameterisation.
     *
     *
     */
    Eigen::MatrixXi delaunayFaces;
    delaunayToEigen(dt, delaunayFaces);
    inMesh.delaunayFaces = delaunayFaces;

    for (int i = 0; i < delaunayFaces.rows(); i++)
    {
        if (delaunayFaces(i, 0) > pts.size()) std::cout << "Found face with bad index: " << delaunayFaces(i, 0);
        if (delaunayFaces(i, 1) > pts.size()) std::cout << "Found face with bad index: " << delaunayFaces(i, 1);
        if (delaunayFaces(i, 2) > pts.size()) std::cout << "Found face with bad index: " << delaunayFaces(i, 2);
    }

    std::cout << std::endl << "Running Lloyd Relaxation: " << std::endl;
    lloydRelaxation(dt, inMesh.parameterisedVerts);
}


void lloydRelaxation(Triangulation& inTri, Eigen::MatrixXd& outVerts)
{
    //Initialise voronoi diagram
    VoronoiDiag vd(inTri);

    int vert = 0;
    //Iterate over vertices
    for (auto iter = inTri.vertices_begin();
            iter != inTri.vertices_end();
            iter++)
    {
        //Find corresponding cell, convert to polygon, do area().
        //First get cell verts (why is this so messy whyyy)
        auto cell = vd.dual(iter);
        std::vector<boostPoint> cellVerts;
        auto ec_start = cell->ccb();
        auto ec = ec_start;
        do
        {
            if (ec->has_source()) cellVerts.push_back(
                        boostPoint(ec->source()->point().x(),
                                   ec->source()->point().y()));
        } while(++ec != ec_start);

        //Construct a boost polygon and get the centroid.
        boostPolygon poly;
        boostPoint centroid;
        boost::geometry::assign_points(poly, cellVerts);
        boost::geometry::centroid(poly, centroid);
        //std::cout << "Centroid: " << centroid.x() << ", " << centroid.y() << std::endl;

        //Assign the centroid to the output
        outVerts(vert, 0) = centroid.x();
        outVerts(vert, 1) = centroid.y();
        vert++;
    }
}

bool delaunayToEigen(Triangulation& in, Eigen::MatrixXi& outFaces){

    //I don't know how to get the number of faces in the delaunay triangulation
            //in.number_of_faces(), ;) -Ben
    //Get non-infinite faces because according to CGAL this shouldn't be an easy thing to do. Bastards.

    outFaces.resize(in.number_of_faces(), 3);
    int row= 0;
    for(auto f_it = in.finite_faces_begin(); f_it != in.finite_faces_end(); ++f_it){
        outFaces(row, 0) = f_it->vertex(0)->info();
        outFaces(row, 1) = f_it->vertex(1)->info();
        outFaces(row, 2) = f_it->vertex(2)->info();
        row++;
    }
    return true;
}