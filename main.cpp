#include <igl/viewer/Viewer.h>
#include <igl/jet.h>
#include <trimesh.h>
#include <trimesh_types.h>
#include <thread>
#include <stdio.h>
#define getSign(a) (a/std::abs(a))

#define MPI 3.1415926536

//Mesh data in Eigen format
Eigen::MatrixXd meshVerts, meshNorms;
Eigen::MatrixXi meshFaces;

//Reformatted mesh as Trimesh structure
trimesh::trimesh_t fullMesh;

//Laplace matrices
Eigen::SparseMatrix<double> uniformLaplacian,
        cotanLaplacian;

//Vertex curvatures
std::vector<double> gaussCurvatures, uniformCurvatures, cotanCurvatures;

//Convert triangles from the Eigen matrix to the trimesh format
trimesh::triangle_t* convertTris(Eigen::MatrixXi& inFaces)
{
    int rows = inFaces.rows();
    trimesh::triangle_t* outTris = static_cast<trimesh::triangle_t *>(malloc(sizeof(trimesh::triangle_t) * rows));
    auto iterator = outTris;
    for (int i = 0; i < rows; i++)
    {
        Eigen::RowVector3i row = inFaces.row(i);
        iterator->v[0] = row(0);
        iterator->v[1] = row(1);
        iterator->v[2] = row(2);
        iterator++;
    }
    return outTris;
}

//Clear the viewer window and redraw the mesh.
void redraw_mesh(igl::viewer::Viewer &viewer)
{
    viewer.data.clear();
    viewer.data.set_mesh(meshVerts, meshFaces);
}

/*
void compute_curvatures()
{
    mean_curvature(meshVerts, fullMesh, uniformCurvatures, uniformLaplacian, uniform);
    mean_curvature(meshVerts, fullMesh, cotanCurvatures, cotanLaplacian, cotangent);
    gaussian_curvature(meshVerts, fullMesh, gaussCurvatures);
}*/

// This function is called every time a keyboard button is pressed
bool key_down(igl::viewer::Viewer& viewer, unsigned char key, int modifier)
{
    //std::cout<<"Key: "<<key<<" "<<(unsigned int)key<<std::endl;
    if (key == ' ')
    {
        viewer.core.align_camera_center(meshVerts, meshFaces);
        std::cout << "Recenter Camera" << std::endl;
    }
    return false;
}

void print_controls()
{   std::cout << std::endl;
    std::cout << "# New Key Bindings #" << std::endl;
    std::cout << "(Spacebar) : Recenter camera" << std::endl;
    std::cout << std::endl;
}

int main(int argc, char *argv[])
{
    //Thread setup
    //unsigned concurrentThreadsSupported = std::thread::hardware_concurrency();
    //std::vector<std::thread> threads(concurrentThreadsSupported);
    std::string fileName = argv[1];
    bool meshLoad = igl::readOFF(fileName, meshVerts, meshFaces);
    if (!meshLoad)std::cout << "Failed to load " << fileName << std::endl;
    if (argv[2]) eigenCount = std::stoi(argv[2]);
    if (argv[3]) smoothStep = std::stod(argv[3], nullptr);

    std::cout << "Vertices: " << meshVerts.size() << std::endl;
    std::cout << "Faces: " << meshFaces.size() << std::endl;

    //Center mesh at (0,0,0)
    Eigen::Matrix3d ident;
    ident.setIdentity();
    Eigen::Vector3d baryCenter;
    compute_barycenter(meshVerts, baryCenter);
    baryCenter *= -1.0;
    transform_vertices(meshVerts, baryCenter, ident);

    igl::viewer::Viewer viewer;
    viewer.callback_key_down = &key_down;
    print_controls();

    //Construct trimesh for half-edge data structure access.
    trimesh::triangle_t* triBuffer = convertTris(meshFaces);
    std::vector<trimesh::edge_t> edgeBuffer;
    unordered_edges_from_triangles(meshFaces.rows(), triBuffer, edgeBuffer);
    fullMesh.build(meshVerts.rows(), meshFaces.rows(), triBuffer, edgeBuffer.size(), &edgeBuffer[0]);
    delete(triBuffer);

    uniformLaplacian = Eigen::SparseMatrix<double>(meshVerts.rows(), meshVerts.rows());
    cotanLaplacian = Eigen::SparseMatrix<double>(meshVerts.rows(), meshVerts.rows());

    compute_curvatures();

    viewer.data.set_mesh(meshVerts, meshFaces);

    Eigen::RowVector3d col;
    col << 0.4, 0.4, 0.4;
    viewer.data.set_colors(col);

    redraw_mesh(viewer);
    viewer.launch();

}
