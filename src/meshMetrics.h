//
// Created by Ben on 13/05/2018.
//
#pragma once
#include "dataStructures.h"

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