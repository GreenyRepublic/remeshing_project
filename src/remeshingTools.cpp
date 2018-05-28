//
// Created by Ben on 19/05/2018.
//

#include "remeshingTools.h"


void barycentricCoord(Eigen::Vector2d& point, Eigen::Vector2d& A, Eigen::Vector2d& B, Eigen::Vector2d& C, Eigen::Vector3d& out)
{
    Eigen::RowVector2d v0, v1, v2;
    v0 = B - A;
    v1 = C - A;
    v2 = point - A;

    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d11 = v1.dot(v1);
    float d20 = v2.dot(v0);
    float d21 = v2.dot(v1);
    float denom = d00 * d11 - d01 * d01;
    out(1) = (d11 * d20 - d01 * d21) / denom;
    out(2) = (d00 * d21 - d01 * d20) / denom;
    out(0) = 1.0f - out(1) - out(2);
}

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
        Eigen::Vector3d baryCoord;
        Eigen::Vector2d a, b, c;
        a = tempIn.parameterisedVerts.row(triIndices(0));
        b = tempIn.parameterisedVerts.row(triIndices(1));
        c = tempIn.parameterisedVerts.row(triIndices(2));
        barycentricCoord(vert,a, b, c, baryCoord);

        //Assign new vert to final outMesh
        outMesh.meshVerts(i, 0) = baryCoord(0) * tempIn.meshVerts(i,0);
        outMesh.meshVerts(i, 1) = baryCoord(1) * tempIn.meshVerts(i,1);
        outMesh.meshVerts(i, 2) = baryCoord(2) * tempIn.meshVerts(i,2);
    }
    outMesh.parameterisedVerts = tempOut.parameterisedVerts;
    std::cout << "Remeshing complete!" << std::endl;
}