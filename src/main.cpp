#include "dataStructures.h"
#include "meshMetrics.h"
#include "remeshingTools.h"
#define getSign(a) (a/std::abs(a))
#define MPI 3.1415926536
#define THREAD_COUNT 4
using Clock=std::chrono::high_resolution_clock;

std::shared_ptr<MeshData> activeMesh = nullptr;
std::vector<std::shared_ptr<MeshData>> Meshes;
bool parameterised = false;

//Reformatted mesh as Trimesh structure
trimesh::trimesh_t fullMesh;


//Constructs a Trimesh data structure from the Eigen mesh matrices
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
void redrawMesh(igl::viewer::Viewer &viewer, MeshData &mesh)
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
void setMesh(std::shared_ptr<MeshData> mesh, igl::viewer::Viewer &viewer)
{
    viewer.data.clear();
    activeMesh = mesh;
    if (!parameterised)
    {
        viewer.data.set_mesh(activeMesh->meshVerts, activeMesh->meshFaces);
        viewer.core.align_camera_center(activeMesh->meshVerts, activeMesh->meshFaces);
    } else{
        viewer.data.set_mesh(activeMesh->parameterisedVerts, activeMesh->meshFaces);
        viewer.core.align_camera_center(activeMesh->parameterisedVerts, activeMesh->meshFaces);
    }
}

// This function is called every time a keyboard button is pressed
bool keyDown(igl::viewer::Viewer &viewer, unsigned char key, int modifier)
{
    std::cout<<"Key: "<<key<<" "<<(unsigned int)key<<std::endl;
    unsigned int num = (unsigned int)key - '0';
    std::cout << "Number: " << num << std::endl;
    if (key == ' ')
    {
        viewer.core.align_camera_center(activeMesh->meshVerts, activeMesh->meshFaces);
        std::cout << "Recenter Camera" << std::endl;
    }

    else if (key == 'P')
    {
        std::cout << "Parameterising Mesh..." << std::endl;
        parameterised = !parameterised;
        setMesh(activeMesh, viewer);
    }

    else if (key == 'M')
    {
        std::cout << "Metrics Time!" << std::endl;
        auto metrics = computeMeshMetrics(activeMesh->meshVerts, activeMesh->meshFaces);
        std::cout << "Mean: " << metrics->triAreaMean << std::endl;
        std::cout << "Variance: " << metrics->triAreaVariance << std::endl;
        std::cout << "Largest: " << metrics->triAreaLargest << std::endl;
        std::cout << "Smallest: " << metrics->triAreaSmallest << std::endl;
    }
    else if (num >= 0 && num < 10)
    {
        setMesh(Meshes.at(std::min<unsigned int>((num - 1) % 10, Meshes.size() - 1)), viewer);
        std::cout << "Setting mesh: " << activeMesh->name << std::endl;
    }
    return false;
}

void printControls()
{   std::cout << std::endl;
    std::cout << "# New Key Bindings #" << std::endl;
    std::cout << "(Spacebar) : Recenter camera" << std::endl;
    std::cout << std::endl;
}


int main(int argc, char *argv[]) {
    //Thread setup
    Eigen::initParallel();
    std::thread threadPool[THREAD_COUNT];

    for (int i = 1; i < argc; i++) {
        auto mesh = std::make_shared<MeshData>();
        std::string fileName = argv[i];
        bool meshLoad = igl::readOFF(fileName, mesh->meshVerts, mesh->meshFaces);
        if (!meshLoad) {
            std::cout << "Mesh " << fileName << " not found! Skipping..." << std::endl;
        } else {
            std::cout << "Loaded mesh " << fileName << std::endl;

            //Scale mesh
            unsigned int offset = mesh->meshVerts.rows() / THREAD_COUNT;
            auto t1 = Clock::now();
            for (int i = 0; i < THREAD_COUNT; i++) threadPool[i] = std::thread([](double a, Eigen::MatrixXd& b, unsigned int c, unsigned int d){scaleMesh(a, b, c, d);}, 5.0, mesh->meshVerts, i * offset, (offset * (i + 1)));
            for (int i = 0; i < THREAD_COUNT; i++) threadPool[i].join();

            parameteriseMesh(*mesh);
            scaleMesh(5.0, mesh->parameterisedVerts);

            mesh->name = fileName;
            Meshes.push_back(mesh);
        }
    }
    if (Meshes.size() == 0) {
        std::cout << "No meshes found! Exiting...";
        return -1;
    }

    igl::viewer::Viewer viewer;
    viewer.callback_key_down = &keyDown;
    printControls();

    //Construct trimesh for half-edge data structure access.
    /*trimesh::triangle_t* triBuffer = convertTris(meshFaces);
    std::vector<trimesh::edge_t> edgeBuffer;
    unordered_edges_from_triangles(meshFaces.rows(), triBuffer, edgeBuffer);
    fullMesh.build(meshVerts.rows(), meshFaces.rows(), triBuffer, edgeBuffer.size(), &edgeBuffer[0]);
    delete(triBuffer);*/

    Eigen::RowVector3d col;
    col << 0.4, 0.4, 0.4;
    viewer.data.set_colors(col);

    setMesh(Meshes[0], viewer);

    viewer.launch();
}

