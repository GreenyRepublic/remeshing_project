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
    inMesh.parameterisedVerts = tempIn.parameterisedVerts;

    //Parameter-space retriangulation loop.
    for (int i = 0; i < iterations; i++) delaunayTriangulation(tempIn, tempOut);

    //std::cout << "Re-triangulation Complete!" << std::endl;

    //Pull back into 3d space
    //tempIn now contains original parameterisation, tempOut contains remeshed parameterisation
    //Since CGAL is being an ass we will have to do this lookup the nasty way
    //Loop over all faces per vertex until we find the matching one.
    outMesh.meshFaces = tempOut.meshFaces;
    outMesh.parameterisedVerts = tempOut.parameterisedVerts;
    outMesh.meshVerts.resize(tempOut.parameterisedVerts.rows(), 3);
    for (int i = 0; i < tempOut.parameterisedVerts.rows(); i++)
    {
        Eigen::RowVector3d baryCoord;
        Eigen::RowVector2d a, b, c;
        //Find the owning triangle
        Eigen::RowVector2d vert = tempOut.parameterisedVerts.row(i);
        Eigen::RowVector3i indices;

        for (int j = 0; j < inMesh.meshFaces.rows(); j++)
        {
            Eigen::RowVector2d a, b, c;
            a = tempIn.parameterisedVerts.row(inMesh.meshFaces(j,0));
            b = tempIn.parameterisedVerts.row(inMesh.meshFaces(j,1));
            c = tempIn.parameterisedVerts.row(inMesh.meshFaces(j,2));

            igl::barycentric_coordinates(vert, a, b, c, baryCoord);
            if (baryCoord(0) >= 0.0 && baryCoord(0) <= 1.0 &&
                baryCoord(1) >= 0.0 && baryCoord(1) <= 1.0 &&
                baryCoord(2) >= 0.0 && baryCoord(2) <= 1.0)
            {
                indices = inMesh.meshFaces.row(j);
                break; }
        }

        //Assign new vert to final outMesh
        outMesh.meshVerts.row(i) = (baryCoord(0) * inMesh.meshVerts.row(indices(0))) +
                (baryCoord(1) * inMesh.meshVerts.row(indices(1))) +
                (baryCoord(2) * inMesh.meshVerts.row(indices(2)));
    }
    outMesh.parameterisedVerts = tempOut.parameterisedVerts;
}