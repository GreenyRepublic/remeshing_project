//
// Created by Ben on 13/05/2018.
//

#include "meshMetrics.h"
#include <chrono>

#define LIMIT 1.8E100

double meshRadius(Eigen::MatrixXd& inVerts)
{
    Eigen::RowVector3d largest, smallest;

    largest << -LIMIT, -LIMIT, -LIMIT;
    smallest << LIMIT, LIMIT, LIMIT;

    for (int i = 0; i < inVerts.rows(); i++)
    {
        auto vert = inVerts.row(i);
        if (vert(0) > largest(0) && vert(1) > largest(1) && vert(2) > largest(2)) largest = vert;
        else if (vert(0) < smallest(0) && vert(1) > smallest(1) && vert(2) > smallest(2)) smallest = vert;
    }
    return std::sqrt((largest - smallest).norm())/2.0;
}

void scaleMesh(double scaleFactor, Eigen::MatrixXd& inVerts, unsigned int startInd, unsigned int endInd)
{
    for (int i = startInd; i < std::min<int>(endInd, inVerts.rows()); i++) inVerts.row(i) = inVerts.row(i) * scaleFactor;
}

void scaleMesh(double scaleFactor, Eigen::MatrixXd& inVerts, unsigned int startInd)
{
    scaleMesh(scaleFactor, inVerts, startInd, inVerts.rows());
}

void scaleMesh(double scaleFactor, Eigen::MatrixXd& inVerts)
{
    scaleMesh(scaleFactor, inVerts, 0);
}

std::unique_ptr<MeshMetrics> computeMeshMetrics(Eigen::MatrixXd& inVerts, Eigen::MatrixXi& inTris)
{
    auto outMetrics = std::make_unique<MeshMetrics>();
    std::vector<double> triAreas;
    double totalArea,
        smallestArea,
        largestArea;
    totalArea = 0.0;
    largestArea = 0.0;
    smallestArea = 10000000000.0;

    //First compute areas
    for (int i = 0; i < inTris.rows(); i++)
    {
        Eigen::RowVector3d vecA = inVerts.row(inTris(i,1));
        Eigen::RowVector3d vecB = inVerts.row(inTris(i,2));

        double area = 0.5 * (vecA.norm() * vecB.norm()) *
                std::sin(std::acos(vecA.normalized().dot(vecB.normalized())));
        triAreas.push_back(area);
        totalArea += area;
        if (area > largestArea) largestArea = area;
        if (area < smallestArea) smallestArea = area;
    }

    outMetrics->triAreaMean = totalArea/triAreas.size();
    outMetrics->triAreaSmallest = smallestArea;
    outMetrics->triAreaLargest = largestArea;

    //Compute variance
    double variance = 0.0;
    for (auto val : triAreas) variance += val * val;
    outMetrics->triAreaVariance = (variance/(triAreas.size() - 1)) - (outMetrics->triAreaMean * outMetrics->triAreaMean);

    return outMetrics;
}
