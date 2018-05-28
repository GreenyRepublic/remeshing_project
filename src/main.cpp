#include "dataStructures.h"
#include "meshMetrics.h"
#include "remeshingTools.h"
#include "delaunayTriangulation.h"
using Clock=std::chrono::high_resolution_clock;

MeshData activeMesh;
std::vector<MeshData> Meshes;
bool parameterised = false;
int iterations = 1;

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
void redrawMesh(igl::viewer::Viewer& viewer, MeshData& mesh)
{
    viewer.data.clear();
    viewer.data.set_mesh(mesh.meshVerts, mesh.meshFaces);
}

void barycenter3(Eigen::MatrixXd& inVerts, Eigen::RowVector3d& center)
{
    center.setZero();
    for (int i = 0; i < inVerts.rows(); i++)
    {
        center += inVerts.row(i);
    }
    center /= inVerts.rows();
}

void barycenter2(Eigen::MatrixXd& inVerts, Eigen::RowVector2d& center)
{
    center.setZero();
    for (int i = 0; i < inVerts.rows(); i++)
    {
        center += inVerts.row(i);
    }
    center /= inVerts.rows();
}

void centerMesh(MeshData& mesh)
{
    if (!parameterised && mesh.meshVerts.rows() != 0)
    {
        Eigen::RowVector3d bary;
        barycenter3(mesh.meshVerts, bary);
        for (int i = 0; i < mesh.meshVerts.rows(); i++) mesh.meshVerts.row(i) -= bary;
    }
    else
    {
        Eigen::RowVector2d bary;
        barycenter2(mesh.parameterisedVerts, bary);
        for (int i = 0; i < mesh.parameterisedVerts.rows(); i++) mesh.parameterisedVerts.row(i) -= bary;
    }
}

//Auxilliary for libigl's built in setmesh() that handles the new MeshData struct
void setMesh(MeshData& mesh, igl::viewer::Viewer &viewer)
{
    viewer.data.clear();
    activeMesh = mesh;
    //std::cout << "Normal stats: " << activeMesh->meshVerts.rows() << " verts. " << activeMesh->meshFaces.rows() << " tris." << std::endl;
    //std::cout << "Param stats: " << activeMesh->parameterisedVerts.rows() << " verts. " << activeMesh->delaunayFaces.rows() << " tris." << std::endl;

    if (!parameterised && activeMesh.meshVerts.rows() != 0)
    {
        viewer.data.set_mesh(activeMesh.meshVerts, activeMesh.meshFaces);
        //centerMesh(activeMesh);
        viewer.core.align_camera_center(activeMesh.meshVerts, activeMesh.meshFaces);
    } else if (activeMesh.parameterisedVerts.rows() != 0){
        viewer.data.set_mesh(activeMesh.parameterisedVerts, activeMesh.meshFaces);
        //centerMesh(activeMesh);
        viewer.core.align_camera_center(activeMesh.parameterisedVerts, activeMesh.meshFaces);
    }
}

// This function is called every time a keyboard button is pressed
bool keyDown(igl::viewer::Viewer &viewer, unsigned char key, int modifier)
{
    std::cout<<"Key: "<<key<<" "<<(unsigned int)key<<std::endl;
    unsigned int num = (unsigned int)key - '0';
    if (key == ' ')
    {
        if (!parameterised)
            viewer.core.align_camera_center(activeMesh.meshVerts, activeMesh.meshFaces);
        else
            viewer.core.align_camera_center(activeMesh.parameterisedVerts, activeMesh.meshFaces);

        std::cout << "Recenter Camera" << std::endl;
    }

    else if (key == 'P')
    {
        parameterised = !parameterised;
        std::cout << "Parameterised View: " ;
        if (parameterised) std::cout << " ON" << std::endl;
        else std::cout << " OFF" << std::endl;
        setMesh(activeMesh, viewer);
    }

    else if (key == 'D'){
        std::cout << "Remeshing with " << iterations << " iterations.";
        auto t1 = Clock::now();
        MeshData newMesh;
        remesh(activeMesh, newMesh, iterations);
        auto t2 = Clock::now();

        std::cout << "Remeshing completed in "
                  << ((double)(std::chrono::duration_cast<std::chrono::milliseconds >(t2 - t1).count())/1000.0)
                  << " seconds" << std::endl;

        setMesh(newMesh, viewer);
        Meshes.push_back(newMesh);
    }
    else if (key == 'M')
    {
        std::cout << "Metrics Time!" << std::endl;
        auto metrics = computeMeshMetrics(activeMesh.meshVerts, activeMesh.meshFaces);
        std::cout << "Mean: " << metrics->triAreaMean << std::endl;
        std::cout << "Variance: " << metrics->triAreaVariance << std::endl;
        std::cout << "Largest: " << metrics->triAreaLargest << std::endl;
        std::cout << "Smallest: " << metrics->triAreaSmallest << std::endl;
    }
    else if (key == 'E'){
        //Evaluation
        std::cout << "Evaluation" << std::endl;
        Eigen::VectorXd cr, ir;
        igl::circumradius(activeMesh.meshVerts, activeMesh.meshFaces, cr);
        igl::inradius(activeMesh.meshVerts, activeMesh.meshFaces, ir);
        //Calculating aspect ratio as the circumradius of each triangle
        //divided by twice the inradius of each triangle
        Eigen::VectorXd aspectRatio = cr.cwiseProduct(ir.cwiseInverse())*0.5;
        //Displaying the mean aspect ratio for the mesh
        double mean = aspectRatio.mean();
        std::cout << "Mean aspect ratio: " << mean << std::endl;

    }
    else if (num >= 0 && num < 10)
    {
        setMesh(Meshes.at(std::min<unsigned int>((num - 1) % 10, Meshes.size() - 1)), viewer);
        std::cout << "Setting mesh: " << activeMesh.name << std::endl;
    }
    return false;
}

void printControls()
{   std::cout << std::endl;
    std::cout << "# New Key Bindings #" << std::endl;
    std::cout << "0-9: Set mesh" << std::endl;
    std::cout << "D: Remesh current mesh" << std::endl;
    std::cout << "E: Compute mesh evaluation metrics" << std::endl;
    std::cout << "P: Toggle parameterised mesh view" << std::endl;
    std::cout << "(Spacebar) : Recenter camera" << std::endl;
    std::cout << std::endl;
}


int main(int argc, char *argv[]) {

    MeshData mesh;
    std::string fileName = argv[1];
    bool meshLoad = igl::readOFF(fileName, mesh.meshVerts, mesh.meshFaces);
    if (!meshLoad) {
        std::cout << "Mesh " << fileName << " not found! Skipping..." << std::endl;
    } else {
        std::cout << "Loaded mesh " << fileName << std::endl;
        parameterise(mesh);
        //Scale mesh
        mesh.name = fileName;
        Meshes.push_back(mesh);
    }
    if (argc == 3)
    {
        std::cout << std::stoi(argv[2]) << std::endl;
        iterations = std::stoi(argv[2]);
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

