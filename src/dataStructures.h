//
// Created by Ben on 19/05/2018.
//
#pragma once

#include <igl/viewer/Viewer.h>
#include <igl/jet.h>
#include <igl/boundary_loop.h>
#include <igl/map_vertices_to_circle.h>
#include <igl/circumradius.h>
#include <igl/inradius.h>
#include <igl/harmonic.h>
#include <igl/lscm.h>
#include <trimesh.h>
#include <trimesh_types.h>
#include <thread>
#include <stdio.h>
#include <algorithm>
#include <memory>
#include <numeric>

struct MeshData
{
    std::string name;
    Eigen::MatrixXd meshVerts;
    Eigen::MatrixXi meshFaces;
    Eigen::MatrixXd parameterisedVerts;
};
