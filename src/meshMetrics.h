//
// Created by Ben on 13/05/2018.
//

#include <igl/viewer/Viewer.h>
#include <igl/jet.h>
#include <trimesh.h>
#include <trimesh_types.h>
#include <thread>
#include <stdio.h>
#include <algorithm>
#include <memory>
#include <numeric>

#ifndef REMESHING_PROJECT_MESHMETRICS_H
#define REMESHING_PROJECT_MESHMETRICS_H

#endif //REMESHING_PROJECT_MESHMETRICS_H

struct MeshMetrics
{
    double triAreaVariance,
           triAreaMean,
           triAreaSmallest,
           triAreaLargest;
};

/*Crunches numbers and spits out the result*/
std::unique_ptr<MeshMetrics> computeMeshMetrics(Eigen::MatrixXd&, Eigen::MatrixXi&);
double meshRadius(Eigen::MatrixXd&);

void scaleMesh(double, Eigen::MatrixXd&);
void scaleMesh(double, Eigen::MatrixXd&, unsigned int);
void scaleMesh(double, Eigen::MatrixXd&, unsigned int, unsigned int);