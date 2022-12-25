#include "edges.h"
#include "euler_characteristic.h"
#include <igl/read_triangle_mesh.h>
#include <igl/is_boundary_edge.h>
#include <igl/euler_characteristic.h>
#include <igl/opengl/glfw/Viewer.h>

int main(int argc, char *argv[])
{
  Eigen::MatrixXd V;
  Eigen::MatrixXi F;
  // Load in a mesh
  igl::read_triangle_mesh(argc>1 ? argv[1] : "../data/bunny.off", V, F);

  Eigen::MatrixXi E = edges(F);

  std::cout << "vertex count of mesh: " << V.rows() << std::endl;
  std::cout << "face count of mesh: " << F.rows() << std::endl;

  std::cout << "Edge list E is "<<E.rows()<<"x"<<E.cols()<<std::endl;
  igl::edges(F, E);
  std::cout << "result is :" << E.rows() << " x " << E.cols() << std::endl;

  int Chi = euler_characteristic(F);
  std::cout << "Euler Characteristic: "<<Chi<<std::endl;

  Chi = igl::euler_characteristic(F);
  std::cout << "result of Euler Characteristic: "<< Chi << std::endl;

  // Create a libigl Viewer object 
  igl::opengl::glfw::Viewer viewer;
  // Set the vertices and faces for the viewer
  viewer.data().set_mesh(V, F);
  // Launch a viewer instance
  viewer.launch();
  return 0;
}

