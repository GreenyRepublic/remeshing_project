//
// Created by Ben on 19/05/2018.
//
#pragma once
#include "dataStructures.h"
#include "delaunayTriangulation.h"

void barycentricCoord(Eigen::Vector2d&, Eigen::Vector2d&, Eigen::Vector2d&, Eigen::Vector2d&, Eigen::Vector3d&);
void remesh(MeshData&, MeshData&, int = 1);
