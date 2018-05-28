//
// Created by Ben on 19/05/2018.
//

#include "remeshingTools.h"

void parameteriseMesh(MeshData& inMesh)
{
    Eigen::VectorXi boundaryData, boundaryIndices(2);
    igl::boundary_loop(inMesh.meshFaces, boundaryData);

    Eigen::MatrixXd bnd_uv;
    igl::map_vertices_to_circle(inMesh.meshVerts,boundaryData,bnd_uv);

    // Harmonic parametrization for the internal vertices
    igl::harmonic(inMesh.meshVerts,inMesh.meshFaces,boundaryData,bnd_uv,1,inMesh.parameterisedVerts);

    /*
    //Selecting two boundary points
    boundaryIndices(0) = boundaryData(0);
    boundaryIndices(1) = boundaryData((int)std::round(boundaryData.size()/2));
    Eigen::MatrixXd bc(2,2);
    bc << 0, 0, 1, 0;

    igl::lscm(inMesh.meshVerts, inMesh.meshFaces, boundaryIndices, bc, inMesh.parameterisedVerts);
     */
}