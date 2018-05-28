//
// Created by Ben on 19/05/2018.
//
#pragma once
#include "dataStructures.h"
#include "delaunayTriangulation.h"
#include "igl/barycentric_coordinates.h"

void parameterise(MeshData&);
void remesh(MeshData&, MeshData&, int = 1);
