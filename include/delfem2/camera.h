/*
 * Copyright (c) 2019 Nobuyuki Umetani
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

/**
 * @file camera class that define projection and model-view transformation.
 * @details this file should be stand alone
 */

#ifndef DFM2_CAMERA_H
#define DFM2_CAMERA_H

#include <ostream>
#include <math.h>
#include <stdio.h> // memcpy
#include <string.h>

// ---------------------------------------------------

namespace delfem2{

void glhFrustumf2(float *matrix, float left, float right, float bottom, float top,
                  float znear, float zfar);
void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio,
                      float znear, float zfar);
void glhTranslatef2(float *matrix, float x, float y, float z);
void glhLookAtf2(float *matrix,
                 float eyex, float eyey, float eyez,
                 float cntx, float cnty, float cntz,
                 float upx, float upy, float upz );

// ----------------------------------------------------


void screenUnProjection(float vout[3],
                        const float v[3],
                        const float mMV[16],
                        const float mPj[16]);

void screenUnProjectionDirection (float vo[3],
                                  const float vi[3],
                                  const float mMV[16],
                                  const float mPj[16]);

// ----------------------------------------------------


enum CAMERA_ROT_MODE
{
  CAMERA_ROT_YTOP,
  CAMERA_ROT_ZTOP,
  CAMERA_ROT_TBALL
};

class CCamera
{
public:
  CCamera(){
    is_pars = false;
    fovy = 60;
    
    view_height = 1.0;
    scale = 1.0;
    
    trans[0] = 0;
    trans[1] = 0;
    trans[2] = 0;
    
    camera_rot_mode = CAMERA_ROT_YTOP;

    psi = 0;
    theta = 0;
    
    Quat_tball[0]=1;
    Quat_tball[1]=0;
    Quat_tball[2]=0;
    Quat_tball[3]=0;
  }
  
  // -----------------------
  // cost methods from here
  
  void Affine4f_Projection(float mP[16], double asp, double depth) const;
  void Affine4f_ModelView(float mMV[16]) const;
  
  // ------------------------
  
  void Scale(double s);
  void Rot_Camera(double dx, double dy);
  void Pan_Camera(double dx, double dy);
private:
public:
  bool is_pars;
  double fovy;
  double scale;
  double view_height;
  double trans[3];
  
  CAMERA_ROT_MODE camera_rot_mode;
  
  // ytop
  double theta;
  double psi;
  
  // tball
  double Quat_tball[4];
};


std::ostream &operator<<(std::ostream &output, CCamera& c);
std::istream &operator>>(std::istream &input, CCamera& c);

} // namespace delfem2

#endif
