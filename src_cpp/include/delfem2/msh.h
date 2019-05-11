/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifndef MSH_H
#define MSH_H

//#include <string>
#include <vector>
//#include <fstream>

////////////////////////////////////////////////////////////////////////
// work on points

void updateMinMaxXYZ(double& x_min, double& x_max,
                     double& y_min, double& y_max,
                     double& z_min, double& z_max,
                     double x, double y, double z);
void GetCenterWidth(double& cx, double& cy, double& cz,
                    double& wx, double& wy, double& wz,
                    const int nXYZ, const double* paXYZ);
void GetCenterWidth(double& cx, double& cy, double& cz,
                    double& wx, double& wy, double& wz,
                    const std::vector<double>& aXYZ);
void GetCenterWidth(double cw[6],
                    const std::vector<double>& aXYZ);
void GetCenterWidthGroup(double& cx, double& cy, double& cz,
                         double& wx, double& wy, double& wz,
                         const std::vector<double>& aXYZ,
                         const std::vector<int>& aElem,
                         const int nnoel,
                         int igroup,
                         const std::vector<int>& aIndGroup);
void GetCenterWidthGroup(double& cx, double& cy, double& cz,
                         double& wx, double& wy, double& wz,
                         const std::vector<double>& aXYZ,
                         const std::vector<int>& aElemInd,
                         const std::vector<int>& aElem,
                         int igroup,
                         const std::vector<int>& aIndGroup);
void GetCenterWidth3DGroup(double cw[6],
                           ////
                           const std::vector<double>& aXYZ,
                           const std::vector<int>& aElemInd,
                           const std::vector<int>& aElem,
                           int igroup,
                           const std::vector<int>& aIndGroup);
// local coordinate
void GetCenterWidthLocal(double& lcx, double& lcy, double& lcz,
                         double& lwx, double& lwy, double& lwz,
                         const std::vector<double>& aXYZ,
                         const double lex[3],
                         const double ley[3],
                         const double lez[3]);
void MinMaxXYZ(double mm[6],
               const std::vector<double>& aXYZ);


//////////////////////

// Bryant angle
void Rotate(std::vector<double>& aXYZ,
            double radx, double rady, double radz);
void Translate(double tx, double ty, double tz,
               std::vector<double>& aXYZ);
void Translate(std::vector<double>& aXYZ,
               double tx, double ty, double tz);
void Translate(double tx, double ty, double tz,
               const unsigned int nnode_, double* pXYZs_);
void Scale(double s,
           std::vector<double>& aXYZ);
void Scale(double s,
           const unsigned int nnode_, double* pXYZs_);
double Size(const std::vector<double>& aXYZ);
void Normalize(std::vector<double>& aXYZ,
               double s = 1.0);

////////////////////////////////////////////////////////////////////////////////////

void CenterOfGravity(double& cgx, double& cgy, double& cgz,
                     const std::vector<double>& aXYZ);
void CenterOfGravity_Tri(double& cgx, double& cgy, double& cgz,
                         int itri,
                         const std::vector<double>& aXYZ,
                         const std::vector<int>& aTri);
double CenterOfGravity_TriMsh3DFlg_Shell(double& cgx, double& cgy, double& cgz,
                                         const std::vector<double>& aXYZ,
                                         const std::vector<int>& aTri,
                                         int iflg,
                                         const std::vector<int>& aFlg);
void CenterOfGravity_Shell(double& cgx, double& cgy, double& cgz,
                           const std::vector<double>& aXYZ,
                           const std::vector<int>& aTri);
void CenterOfGravity_Solid(double& cgx, double& cgy, double& cgz,
                           const std::vector<double>& aXYZ,
                           const std::vector<int>& aTri);

////////////////////////////////////////////////////////////////////////////////////

void RemoveUnreferencedPoints3D(std::vector<double>& aXYZOut,
                                std::vector<int>& aTriOut,
                                std::vector<int>& aMapInOut,
                                const std::vector<double>& aXYZIn,
                                const std::vector<int>& aTriIn);
void MakeNormal(std::vector<double>& aNorm,
                const std::vector<double>& aXYZ,
                const std::vector<int>& aTri);
void Quality_MeshTri2D(double& max_aspect, double& min_area,
                       const double* aXY,
                       const int* aTri, int nTri);

///////////////////////////////////////////////////////////////////////////////
// set primitive mesh

void MeshQuad2D_Grid(std::vector<double>& aXYZ, std::vector<int>& aQuad,
                    int nx, int ny);
// y axis is the pole
void MeshTri3D_Sphere(std::vector<double>& aXYZ, std::vector<int>& aTri,
                      double r,
                      int nla, int nlo);
// y axis is the axis of cylinder
void MeshTri3D_OpenCylinder(std::vector<double>& aXYZ, std::vector<int>& aTri,
                            double r, double l,
                            int nr, int nl);
void MeshTri3D_ClosedCylinder(std::vector<double>& aXYZ, std::vector<int>& aTri,
                              double r, double l,
                              int nr, int nl);
void MeshTri3D_Cube(std::vector<double>& aXYZ, std::vector<int>& aTri,
                    int n);
void MeshTri3D_Disk(std::vector<double>& aXYZ, std::vector<int>& aTri,
                    double r, int nr, int nth);
void MeshQuad3D_CubeVox(std::vector<double>& aXYZ, std::vector<int>& aQuad,
                        double x_min, double x_max,
                        double y_min, double y_max,
                        double z_min, double z_max);
void MeshTri3D_Icosahedron(std::vector<double>& aXYZ,
                           std::vector<int>& aTri);
void SetTopoQuad_CubeVox(std::vector<int>& aQuad);
void ExtrudeTri2Tet(int nlayer, double h,
                    std::vector<double>& aXYZ,
                    std::vector<int>& aTet,
                    const std::vector<double>& aXY,
                    const std::vector<int>& aTri);

//////////////////////////////////////////////////////////////////////

void makeSolidAngle(std::vector<double>& aSolidAngle,
                    const std::vector<double>& aXYZ,
                    const std::vector<int>& aTri);
void makeSolidAngle(std::vector<double>& aSolidAngle,
                    const std::vector<double>& aXYZ,
                    const std::vector<int>& aTri,
                    const std::vector<double>& aNorm,
                    std::vector<int>& elsup_ind,
                    std::vector<int>& elsup);
void LaplacianSmoothing(std::vector<double>& aXYZ,
                        const std::vector<int>& aTri,
                        const std::vector<int>& elsup_ind,
                        const std::vector<int> elsup);
void SubdivisionPoints_QuadCatmullClark(std::vector<double>& aXYZ1,
                                        ///
                                        const std::vector<int>& aQuad1,
                                        const std::vector<int>& aEdgeFace0,
                                        const std::vector<int>& psupIndQuad0,
                                        const std::vector<int>& psupQuad0,
                                        const int* aQuad0, int nQuad0,
                                        const double* aXYZ0, int nXYZ0);
void SubdivisionPoints_Quad(std::vector<double>& aXYZ1,
                            ///
                            const std::vector<int>& aQuad1,
                            const std::vector<int>& aEdgeFace0,
                            const std::vector<int>& psupIndQuad0,
                            const std::vector<int>& psupQuad0,
                            const std::vector<int>& aQuad0,
                            const std::vector<double>& aXYZ0);

void SubdivisionPoints_Hex(std::vector<double>& aXYZ1,
                           ///
                           const std::vector<int>& psupHex0,
                           const std::vector<int>& psupIndHex0,
                           const std::vector<int>& aQuadHex0,
                           const int* aHex0, int nHex0,
                           const double* aXYZ0, int nXYZ0);

//////////////////////////////////////////////////////////////
// raw mesh functions




#endif
