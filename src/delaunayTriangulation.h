//
// Created by maria on 21/05/2018.
//
#pragma once
#include "dataStructures.h"
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_vertex_base_with_info_2.h>
#include <CGAL/Triangulation_data_structure_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>
#include <CGAL/Polygon_2.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_vertex_base_with_info_2<size_t, K> Info;
typedef CGAL::Triangulation_face_base_2<K> Fb;
typedef CGAL::Triangulation_data_structure_2<Info, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;

typedef CGAL::Delaunay_triangulation_adaptation_traits_2<Triangulation> Traits;
typedef CGAL::Voronoi_diagram_2<Triangulation, Traits> VoronoiDiag;

typedef boost::geometry::model::d2::point_xy<double> boostPoint;
typedef boost::geometry::model::polygon<boostPoint> boostPolygon;

typedef Triangulation::Point Point;
typedef Triangulation::Finite_vertices_iterator Vertices_iterator;
typedef Triangulation::Finite_faces_iterator Faces_iterator;
typedef Triangulation::Vertex_handle Vertex_handle;
typedef Triangulation::Face_handle Face_handle;

void delaunayTriangulation(MeshData&);

//Performs Lloyd Relaxation on parameter-space vertices for some iterations
void lloydRelaxation(Triangulation&, Eigen::MatrixXd&);

//Converts CGAL Delaunay triangulation parameter-space mesh to Eigen MatrixXd parameter-space verts.
bool delaunayToEigen(Triangulation& in, Eigen::MatrixXi& outFaces);
bool eigenToDelaunay(Eigen::MatrixXd& inVerts, std::vector<Point>& outPoints);