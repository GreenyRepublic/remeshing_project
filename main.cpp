//#include <windef.h>
#include <igl/viewer/Viewer.h>
#include <igl/jet.h>
#include <trimesh.h>
#include <trimesh_types.h>
#include <thread>
#include <stdio.h>
#include <algorithm>
#define getSign(a) (a/std::abs(a))

#define MPI 3.1415926536

struct MeshData
{
    std::string name;
    Eigen::MatrixXd meshVerts;
    Eigen::MatrixXi meshFaces;
};

std::shared_ptr<MeshData> activeMesh = nullptr;

std::vector<std::shared_ptr<MeshData>> Meshes;
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
void redraw_mesh(igl::viewer::Viewer &viewer, MeshData& mesh)
{
    viewer.data.clear();
    viewer.data.set_mesh(mesh.meshVerts, mesh.meshFaces);
}

/*
void compute_curvatures()
{
    mean_curvature(meshVerts, fullMesh, uniformCurvatures, uniformLaplacian, uniform);
    mean_curvature(meshVerts, fullMesh, cotanCurvatures, cotanLaplacian, cotangent);
    gaussian_curvature(meshVerts, fullMesh, gaussCurvatures);
}*/

//Auxilliary for libigl's built in setmesh() that handles the new MeshData struct
void set_mesh(std::shared_ptr<MeshData> mesh, igl::viewer::Viewer& viewer)
{
    std::cout << "Setting mesh: " << mesh->name << std::endl;
    viewer.data.clear();
    viewer.data.set_mesh(mesh->meshVerts, mesh->meshFaces);
    viewer.core.align_camera_center(activeMesh->meshVerts, activeMesh->meshFaces);
    activeMesh = mesh;
}

// This function is called every time a keyboard button is pressed
bool key_down(igl::viewer::Viewer& viewer, unsigned char key, int modifier)
{
    std::cout<<"Key: "<<key<<" "<<(unsigned int)key<<std::endl;
    unsigned int num = (unsigned int)key - '0';
    std::cout << "Number: " << num << std::endl;
    if (key == ' ')
    {
        viewer.core.align_camera_center(activeMesh->meshVerts, activeMesh->meshFaces);
        std::cout << "Recenter Camera" << std::endl;
    }
    else if (num >= 0 && num < 10)
    {
        set_mesh(Meshes.at(std::min<unsigned int>(num, Meshes.size() - 1)), viewer);
        std::cout << "Setting mesh: " << activeMesh->name << std::endl;
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
    for (int i = 1; i < argc; i++)
    {
        auto mesh = std::make_shared<MeshData>();
        std::string fileName = argv[i];
        bool meshLoad = igl::readOFF(fileName, mesh->meshVerts, mesh->meshFaces);
        if (!meshLoad)
        {
            std::cout << "Mesh " << fileName << " not found! Skipping..." << std::endl;
        }
        else
        {
            std::cout << "Loaded mesh " << fileName << std::endl;
            mesh->name = fileName;
            Meshes.push_back(mesh);
        }
    }
    if (Meshes.size() == 0)
    {
        std::cout << "No meshes found! Exiting...";
        return -1;
    }

    igl::viewer::Viewer viewer;
    viewer.callback_key_down = &key_down;
    print_controls();

    //Construct trimesh for half-edge data structure access.
    /*trimesh::triangle_t* triBuffer = convertTris(meshFaces);
    std::vector<trimesh::edge_t> edgeBuffer;
    unordered_edges_from_triangles(meshFaces.rows(), triBuffer, edgeBuffer);
    fullMesh.build(meshVerts.rows(), meshFaces.rows(), triBuffer, edgeBuffer.size(), &edgeBuffer[0]);
    delete(triBuffer);*/

    Eigen::RowVector3d col;
    col << 0.4, 0.4, 0.4;
    viewer.data.set_colors(col);

    //redraw_mesh(viewer,);
    viewer.launch();
    //set_mesh(Meshes[0], viewer);

}
