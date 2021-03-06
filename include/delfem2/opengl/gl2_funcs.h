/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**
 * @details the file depends on OpenGL 2.x.
 * There are a lot of legacy commands such as glBegin(),glEnd()
 */

#ifndef DFM2_FUNCS_GL2_H
#define DFM2_FUNCS_GL2_H

#include <string>
#include <vector>

namespace delfem2{
namespace opengl{

// x = ax*[x] + bx
// y = ay*[y] + by
void DrawCharacter(int* pChr,
                   double ax, double bx,
                   double ay, double by);

// x = ax*[x] + bx
// y = ay*[y] + by
void DrawCharacter(char ic,
                   double ax, double bx,
                   double ay, double by);


void setSomeLighting();
void setSomeLighting2();
void setSomeLighting3();
void drawFloorShadow(void (*DrawObject)(), float yfloor, float wfloor);


void DrawRectangle_FullCanvas();
void showdepth();

// --------------------------------------------------
void getPosOnScreen_Camera2D(double& x, double& y,
                             int i, int j);
void setGL_Camera2D();


// -------------------
// draw functions

void DrawAxis(double s);

void DrawSphere(int nla, int nlo);
void DrawSphereAt(int nla, int nlo, double rad, double x, double y, double z);
void DrawSphere_Edge(double radius_);

void DrawTorus_Edge(double radius_, double radius_tube_);

void DrawCylinder_Face(const double* dir_, double radius_, const double* cent_);
void DrawCylinder_Edge(const double* dir_, double radius_, const double* cent_);

void DrawPlane_Edge(const double* origin_, const double* normal_);

void DrawBox_MinMaxXYZ(double x_min, double x_max,
                       double y_min, double y_max,
                       double z_min, double z_max);
void DrawBox_MinMaxXYZ(double aabbMinMaxXYZ[6]);
void DrawAABB3D_Edge(double cx, double cy, double cz,
                     double wx, double wy, double wz);
void DrawAABB3D_Edge(const double cw[6]);
void Draw_AABB3D_MinMaxXYZ_Edge(double x_min, double x_max,
                                double y_min, double y_max,
                                double z_min, double z_max);

// -------------
// Draw Point

void DrawPoints2D_Vectors(const double* aXY, int nXY,
                          const double* aVal,
                          int nstride,
                          int noffset,
                          double mag);
void DrawPoints2D_Points(std::vector<double>& aXY);
void DrawPoints3D_Points(std::vector<double>& aXYZ);

// --------------
// Draw Line
void DrawMeshLine3D_Edge(const double* aXYZ,
                         int nXYZ,
                         const unsigned int* aLine,
                         int nLine);
// ------------
// Draw Tri

void DrawMeshTri2D_Face(const std::vector<unsigned int>& aTri,
                        const std::vector<double>& aXY);
void DrawMeshTri2D_FaceDisp2D(const double* aXY, int nXY,
                              const unsigned int* aTri, int nTri,
                              const double* aDisp, int nstride);
void DrawMeshTri2D_Edge(const double* aXY, unsigned int nXY,
                        const unsigned int* aTri, unsigned int nTri);
void DrawMeshTri2D_Edge(const std::vector<unsigned int>& aTri,
                        const std::vector<double>& aXY);

////
void DrawMeshTri3D_FaceEdge(const std::vector<double>& aXYZ,
                            const std::vector<unsigned int>& aTri);
void DrawMeshTri3D_FaceNorm(const double* paXYZ,
                            const unsigned int* paTri, unsigned int nTri);
void DrawMeshTri3D_FaceNorm(const std::vector<double>& aXYZ,
                            const std::vector<unsigned int>& aTri);
void DrawMeshTri3D_FaceNorm(const std::vector<double>& aXYZ,
                            const std::vector<unsigned int>& aTri,
                            const std::vector<double>& aNorm);
void DrawMeshTri3D_FaceNorm(const std::vector<double>& aXYZ,
                            const std::vector<unsigned int>& aTriVtx,
                            const std::vector<double>& aNorm,
                            const std::vector<unsigned int>& aTriNrm);
////
void DrawMeshTri3DPart_FaceNorm(const std::vector<double>& aXYZ,
                            const std::vector<int>& aTri,
                            const std::vector<int>& aIndTri);
void DrawMeshTri3D_FaceNorm_Flg(const std::vector<double>& aXYZ,
                            const std::vector<int>& aTri,
                            int iflg,
                            const std::vector<int>& aFlgTri);
void DrawMeshTri3D_FaceNorm_XYsym(const std::vector<double>& aXYZ,
                              const std::vector<unsigned int>& aTri);
void DrawMeshTri3D_FaceNormEdge(const std::vector<double>& aXYZ,
                            const std::vector<unsigned int>& aTri);
void DrawMeshTri3D_FaceNorm_TexFace(const std::vector<double>& aXYZ,
                                    const std::vector<unsigned int>& aTri,
                                    const std::vector<double>& aTex);
void DrawMeshTri3D_FaceNorm_TexVtx(const std::vector<double>& aXYZ,
                                   const std::vector<unsigned int>& aTri,
                                   const std::vector<double>& aTex);
// Edge 3D
void DrawMeshTri3D_Edge(const double* aXYZ, unsigned int nXYZ,
                        const unsigned int* aTri, unsigned int nTri);
void DrawMeshTri3D_Edge(const std::vector<double>& aXYZ,
                        const std::vector<unsigned int>& aTri);
void DrawMeshTriMap3D_Edge(const std::vector<double>& aXYZ,
                           const std::vector<unsigned int>& aTri,
                           const std::vector<int>& map);

// -----------------
// Draw Quad

void DrawMeshQuad3D_Edge(const double* aXYZ, unsigned int nXYZ,
                         const unsigned int* aQuad, unsigned int nQuad);
void DrawMeshQuad3D_Edge(const std::vector<double>& aXYZ,
                         const std::vector<unsigned int>& aQuad);
void DrawMeshQuad2D_Edge(const double* aXY, unsigned int nXY,
                         const unsigned int* aQuad, unsigned int nQuad);
void DrawMeshQuad2D_Edge(const std::vector<double>& aXY,
                         const std::vector<unsigned int>& aQuad);
void DrawMeshQuad3D_FaceNorm(const double* aXYZ,
                             const unsigned int* aQuad, unsigned int nQuad);
void DrawMeshQuad3D_FaceNorm(const std::vector<double>& aXYZ,
                             const std::vector<unsigned int>& aQuad);

// -------------------
// Draw Tet

void DrawMeshTet3D_Edge(const double* aXYZ, int nXYZ,
                        const unsigned int* aTet, int nTet);
void DrawMeshTet3D_EdgeDisp(const double* aXYZ,
                            const unsigned int* aTet, unsigned int nTet,
                            const double* aDisp,
                            double s0);
void DrawMeshTet3D_FaceNorm(const double* aXYZ,
                            const unsigned int* aTet, unsigned int nTet);
void DrawMeshTet3DSurface_FaceNorm(const std::vector<double>& aXYZ,
                               const std::vector<unsigned int>& aTet,
                               const std::vector<unsigned int>& aTetFace);
void DrawMeshTet3DSurface_Edge(const std::vector<double>& aXYZ,
                           const std::vector<unsigned int>& aTet,
                           const std::vector<unsigned int>& aTetFace);
void DrawMeshTet3D_FaceNormDisp(const double* aXYZ, int nXYZ,
                                const unsigned int* aTet, int nTet,
                                const double* aDisp);

// -------------
// Draw Hex

void DrawMeshHex3D_Edge(const double* aXYZ, int nXYZ,
                        const unsigned int* aHex, int nHex);
void DrawMeshHex3D_FaceNorm(const double* aXYZ,
                            const unsigned int* aHex, unsigned int nHex);
void DrawHex3D_FaceNormDisp(const std::vector<double>& aXYZ,
                           const std::vector<int>& aHex,
                           const std::vector<double>& aDisp);
void Draw_HexMeshFaceDisp(const std::vector<double>& aXYZ,
                          const std::vector<unsigned int>& aHex,
                          const std::vector<double>& aDisp);


// -----------
// Draw Mix

void DrawMeshElem3D_FaceNorm(const std::vector<double>& aXYZ,
                             const std::vector<unsigned int>& aElemInd,
                             const std::vector<unsigned int>& aElem);

void DrawMeshElem3D_FaceNorm(const std::vector<double>& aXYZ,
                             const std::vector<unsigned int>& aElemInd,
                             const std::vector<unsigned int>& aElem,
                             const std::vector<double>& aUV);
void DrawMeshElemPart3D_FaceNorm_TexPoEl(const std::vector<double>& aXYZ,
                                         const std::vector<unsigned int>& aElemInd,
                                         const std::vector<unsigned int>& aElem,
                                         const std::vector<int>& aIndElem,
                                         const std::vector<double>& aUV);


// ------------------------

class CAxisXYZ {
public:
  CAxisXYZ(): len(1.0){
    line_width = 1.0;
  }
  CAxisXYZ(double len): len(len){
    line_width=1.0;
  }
  void Draw() const;
  std::vector<double> MinMaxXYZ() const{
    std::vector<double> mm(6,0);
    mm[1] = len;  mm[3] = len;  mm[5] = len;
    return mm;
  }
public:
  double len;
  double line_width;
};

} // namespace opengl
} // namespace delfem2

#endif /* utility_gl_h */
