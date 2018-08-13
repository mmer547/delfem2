#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <vector>

#include "delfem2/mshio.h"
#include "delfem2/funcs_gl.h"

class CMeshTri{
public:
  void Read(const std::string& fname){
    Load_Ply(fname, aPos, aTri);
  }
  void Draw(){
    DrawMeshTri3D_FaceNorm(aPos, aTri);
  }
public:
  std::vector<int> aTri;
  std::vector<double> aPos;
};

namespace py = pybind11;

PYBIND11_MODULE(geosim, m) {
  m.doc() = "pybind11 example plugin";
  //////
  py::class_<CMeshTri>(m, "CMeshTri")
  .def(py::init<>())
  .def("Read", &CMeshTri::Read)
  .def("Draw", &CMeshTri::Draw)
  .def_readwrite("aTri", &CMeshTri::aTri);
}
