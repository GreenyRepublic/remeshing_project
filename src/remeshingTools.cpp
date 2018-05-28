//
// Created by Ben on 19/05/2018.
//

#include "remeshingTools.h"


void remesh(MeshData &inMesh, MeshData& outMesh, int iterations)
{
    //Temporary working copies of things for safety.
    //Perform all operations on these, transfer data to outMesh at the end.
    MeshData tempIn = inMesh;
    MeshData tempOut;

    //First parameterise
    Eigen::VectorXi boundaryData, boundaryIndices(2);
    igl::boundary_loop(tempIn.meshFaces, boundaryData);

    Eigen::MatrixXd bnd_uv;
    igl::map_vertices_to_circle(tempIn.meshVerts,boundaryData,bnd_uv);

    // Harmonic parametrization for the internal vertices
    igl::harmonic(tempIn.meshVerts,tempIn.meshFaces,boundaryData,bnd_uv,1,tempIn.parameterisedVerts);


    //Parameter-space retriangulation loop.
    for (int i = 0; i < iterations; i++) delaunayTriangulation(tempIn, tempOut);

    //Pull back into 3d space
    //tempIn now contains original parameterisation, tempOut contains remeshed parameterisation
    //Since CGAL is being an ass we will have to do this lookup the nasty way
    //Loop over all faces per vertex until we find the matching one.
    for (int i = 0; i < tempOut.parameterisedVerts.rows(); i++)
    {
        //Find the owning triangle
        Eigen::Vector2d vert = tempOut.parameterisedVerts.row(i);
        boostPoint point(vert(0), vert(1));
        Eigen::RowVector3i triIndices;
        for (int j = 0; j < tempIn.meshFaces.rows(); j++)
        {
            Eigen::RowVector2d tri0, tri1, tri2;
            tri0 = tempIn.parameterisedVerts.row(tempIn.meshFaces(j,0));
            tri1 = tempIn.parameterisedVerts.row(tempIn.meshFaces(j,1));
            tri2 = tempIn.parameterisedVerts.row(tempIn.meshFaces(j,2));

            boostPolygon tri{{boostPoint(tri0(0), tri0(1))},
                             {boostPoint(tri1(0), tri1(1))},
                             {boostPoint(tri2(0), tri2(1))}};
            if (boost::geometry::within(point, tri))
            {
                triIndices << tempIn.meshFaces(j,0), tempIn.meshFaces(j,1), tempIn.meshFaces(j,2);
                std::cout << "Found!" << triIndices << std::endl;
                break;
            }
        }
        //Found tri, now barycenter crunch
        Eigen::Vector3d barycentricCoord;
        igl::barycentric_coordinates(vert,
                                    tempIn.parameterisedVerts.row(triIndices(0)),
                                    tempIn.parameterisedVerts.row(triIndices(1)),
                                    tempIn.parameterisedVerts.row(triIndices(2)),
                                    barycentricCoord);

        //Assign new vert to final outMesh
        outMesh.meshVerts(i, 0) = barycentricCoord(0) * tempIn.meshVerts(i,0);
        outMesh.meshVerts(i, 1) = barycentricCoord(1) * tempIn.meshVerts(i,1);
        outMesh.meshVerts(i, 2) = barycentricCoord(2) * tempIn.meshVerts(i,2);
    }
    outMesh.parameterisedVerts = tempOut.parameterisedVerts;
    std::cout << "Remeshing complete!" << std::endl;
}