//
// Created by Ben on 19/05/2018.
//

#include "remeshingTools.h"

void parameteriseMesh(MeshData& inMesh)
{
    Eigen::VectorXi boundaryData, boundaryIndices(2);
    igl::boundary_loop(inMesh.meshFaces, boundaryData);

    //Selecting two boundary points
    boundaryIndices(0) = boundaryData(0);
    boundaryIndices(1) = boundaryData((int)std::round(boundaryData.size()/2));
    Eigen::MatrixXd bc(2,2);
    bc << 0, 0, 1, 0;

    igl::lscm(inMesh.meshVerts, inMesh.meshFaces, boundaryIndices, bc, inMesh.parameterisedVerts);
}