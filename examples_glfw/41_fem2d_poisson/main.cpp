#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <limits>
#include <vector>

#if defined(_MSC_VER)
  #include <windows.h>
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef EMSCRIPTEN
  #include <emscripten/emscripten.h>
  #define GLFW_INCLUDE_ES3
#endif

#include "delfem2/mshtopo.h"
#include "delfem2/msh.h"
#include "delfem2/dtri.h"
#include "delfem2/mats.h"

#include "delfem2/dtri_v2.h"
#include "delfem2/ilu_mats.h"
#include "delfem2/fem_emats.h"

#include "delfem2/gl2_color.h"
#include "delfem2/gl4_mshcolor.h"
#include "../glfw_funcs.h"

double AreaCGCurve(const std::vector<double>& aCV, double cg[2])
{
  const unsigned int nCV = (int)aCV.size()/2;
  double area = 0;
  cg[0] = 0;
  cg[1] = 0;
  for(unsigned int idiv=0;idiv<nCV;idiv++){
    unsigned int ipo0 = idiv;
    unsigned int ipo1 = idiv+1;
    if( idiv == nCV-1 ){ ipo1 = 0; }
    const double p0[2] = { aCV[ipo0*2+0], aCV[ipo0*2+1] };
    const double p1[2] = { aCV[ipo1*2+0], aCV[ipo1*2+1] };
    const double p2[2] = { 0, 0 };
    double a0 = TriArea2D(p0, p1, p2);
    double cg0[2] = { (p0[0]+p1[0]+p2[0])/3.0, (p0[1]+p1[1]+p2[1])/3.0 };
    cg[0] += cg0[0]*a0;
    cg[1] += cg0[1]*a0;
    area += a0;
  }
  cg[0] /= area;
  cg[1] /= area;
  return area;
}

void MakeRandomCV(unsigned int nCV, std::vector<double>& aCV)
{
  aCV.clear();
  for(unsigned int icv=0;icv<nCV;icv++){
    /*
     {
     aCV.push_back((double)rand()/(RAND_MAX+1.0));
     aCV.push_back((double)rand()/(RAND_MAX+1.0));
     }
     */
    {
      double tht = icv*3.1415*2.0/nCV;
      double r = (double)rand()/(RAND_MAX+1.0);
      double px = r*sin(tht);
      double py = r*cos(tht);
      aCV.push_back(px);
      aCV.push_back(py);
    }
  }
  
  {
    double cnt[2];
    double area = AreaCGCurve(aCV,cnt);
    if( area < 0 ){
      std::vector<double> aCV0;
      for(unsigned int idiv=0;idiv<nCV;idiv++){
        unsigned int idiv0 = nCV-1-idiv;
        aCV0.push_back( aCV[idiv0*2+0] );
        aCV0.push_back( aCV[idiv0*2+1] );
      }
      aCV = aCV0;
      area = -area;
    }
    if( area < 1.0e-5 ){
      aCV.clear();
      return;
    }
  }
}


void MakeCurveSpline(const std::vector<double>& aCV, std::vector<double>& aVecCurve, int ndiv=5)
{
  aVecCurve.resize(0);
  const unsigned int nCV = aCV.size()/2;
  for(unsigned int icv=0;icv<nCV;icv++){
    int icv0=(icv+0)%nCV;
    int icv1=(icv+1)%nCV;
    int icv2=(icv+2)%nCV;
    const double p0[2] = { aCV[icv0*2+0], aCV[icv0*2+1] };
    const double p1[2] = { aCV[icv1*2+0], aCV[icv1*2+1] };
    const double p2[2] = { aCV[icv2*2+0], aCV[icv2*2+1] };
    for(unsigned int idiv=0;idiv<ndiv;idiv++){
      const double t = 1.0-(double)idiv/ndiv;
      const double w[3] = {0.5*t*t, -t*t + t + 0.5, 0.5*(1-t)*(1-t) };
      const double px = w[0]*p0[0] + w[1]*p1[0] + w[2]*p2[0];
      const double py = w[0]*p0[1] + w[1]*p1[1] + w[2]*p2[1];
      aVecCurve.push_back(px);
      aVecCurve.push_back(py);
    }
  }
}

/*
void myGlVertex2D(const std::vector<double>& vec, unsigned int i)
{
  ::glVertex3d(vec[i*2],vec[i*2+1],+0.5);
}

void drawCurve
(const std::vector<double>& vec,
 const std::vector<double>& aVecCurve0)
{
  if( aVecCurve0.size() < 2 ){ return; }
  ::glBegin(GL_LINES);
  const unsigned int nvec = (int)vec.size()/2;
  for(unsigned int ivec=0;ivec<nvec;ivec++){
    unsigned int jvec = ivec+1; if( jvec >= nvec ){ jvec -= nvec; }
    myGlVertex2D(vec,ivec);
    myGlVertex2D(vec,jvec);
  }
  ::glEnd();
  
  ::glBegin(GL_POINTS);
  for(unsigned int ivec=0;ivec<nvec;ivec++){
    myGlVertex2D(vec,ivec);
  }
  ::glEnd();
}
 */



// -----------------------------

double len = 1.1;
std::vector<unsigned int> aTri1;
std::vector<double> aXY1;
std::vector<int> loopIP_ind, loopIP; // vtx on loop

std::vector<double> aVal;
std::vector<int> aBCFlag; // master slave flag

CMatrixSparse<double> mat_A;
std::vector<double> vec_b;
CPreconditionerILU<double> ilu_A;

CNav3D_GLFW nav;
CShader_TriMesh_Scalar shdr0;


// -----------------------------

void MakeMesh(){
  std::vector<double> aCV0; MakeRandomCV(8, aCV0); // current cv
  std::vector<double> aXY0;
  MakeCurveSpline(aCV0, aXY0,20); // current curve
  std::vector< std::vector<double> > aaXY;
  {
    aaXY.resize(1);
    aaXY[0].push_back(-len); aaXY[0].push_back(-len);
    aaXY[0].push_back(-len); aaXY[0].push_back(+len);
    aaXY[0].push_back(+len); aaXY[0].push_back(+len);
    aaXY[0].push_back(+len); aaXY[0].push_back(-len);
  }
  aaXY.push_back(aXY0);
  // ------------------
  std::vector<CVector2> aVec2;
  const double elen = 0.05;
  {
    JArray_FromVecVec_XY(loopIP_ind,loopIP, aVec2,
                         aaXY);
    if( !CheckInputBoundaryForTriangulation(loopIP_ind,aVec2) ){
      return;
    }
    FixLoopOrientation(loopIP,
                       loopIP_ind,aVec2);
    if( elen > 10e-10 ){
      ResamplingLoop(loopIP_ind,loopIP,aVec2,
                     elen );
    }
  }
  {
    std::vector<CEPo2> aPo2D;
    std::vector<ETri> aETri;
    Meshing_SingleConnectedShape2D(aPo2D, aVec2, aETri,
                                   loopIP_ind,loopIP);
    if( elen > 1.0e-10 ){
      CInputTriangulation_Uniform param(1.0);
      std::vector<int> aFlgPnt(aPo2D.size()), aFlgTri(aETri.size());
      MeshingInside(aPo2D,aETri,aVec2, aFlgPnt,aFlgTri,
                    aVec2.size(),0,elen, param);
    }
    MeshTri2D_Export(aXY1,aTri1,
                     aVec2,aETri);
  }
  std::cout<<"  ntri;"<<aTri1.size()/3<<"  nXY:"<<aXY1.size()/2<<std::endl;
}

void InitializeProblem_Scalar()
{
  const int np = (int)aXY1.size()/2;
  aBCFlag.assign(np, 0);
  for(int ip=0;ip<np;++ip){
    const double px = aXY1[ip*2+0];
    const double py = aXY1[ip*2+1];
    if( fabs(fabs(px)-len) < 0.0001 || fabs(fabs(py)-len) < 0.0001 ){
      aBCFlag[ip] = 1;
    }
  }
  /*
  for(int iip=loopIP1_ind[1];iip<loopIP1_ind[2];++iip){
    int ip0 = loopIP1[iip];
    aBCFlag[ip0] = 1;
  }
   */
  std::vector<int> psup_ind, psup;
  JArrayPointSurPoint_MeshOneRingNeighborhood(psup_ind, psup,
                                              aTri1.data(), aTri1.size()/3, 3, (int)aXY1.size()/2);
  JArray_Sort(psup_ind, psup);
  ////
  mat_A.Initialize(np, 1, true);
  mat_A.SetPattern(psup_ind.data(), psup_ind.size(), psup.data(),psup.size());
  ilu_A.Initialize_ILU0(mat_A);
}

void SolveProblem_Poisson()
{
  const int np = (int)aXY1.size()/2;
  const int nDoF = np;
  // -----------------------
  const double alpha = 1.0;
  const double source = 1.0;
  mat_A.SetZero();
  vec_b.assign(nDoF, 0.0);
  MergeLinSys_Poission_MeshTri2D(mat_A,vec_b.data(),
                         alpha,source,
                         aXY1.data(),aXY1.size()/2,
                         aTri1.data(),aTri1.size()/3,
                         aVal.data());
  mat_A.SetBoundaryCondition(aBCFlag.data(),aBCFlag.size(),1);
  setRHS_Zero(vec_b, aBCFlag,0);
  // -----------------------
  std::vector<double> vec_x;
  double conv_ratio = 1.0e-4;
  int iteration = 1000;
  ilu_A.SetValueILU(mat_A);
  ilu_A.DoILUDecomp();
  vec_x.resize(vec_b.size());
  Solve_PCG(vec_b.data(),vec_x.data(),
            conv_ratio,iteration, mat_A,ilu_A);
  // -----------------------
  XPlusAY(aVal,nDoF,aBCFlag,
          1.0,vec_x);
}

// ----------------------------------------------------------

void draw(GLFWwindow* window)
{
  float asp;
  {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    asp = width / (float) height;
      //    std::cout << width << " " << height << " " << asp << std::endl;
  }
  
  ::glClearColor(0.8, 1.0, 1.0, 1.0);
  ::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ::glEnable(GL_DEPTH_TEST);
  ::glDepthFunc(GL_LESS);
  ::glEnable(GL_POLYGON_OFFSET_FILL );
  ::glPolygonOffset( 1.1f, 4.0f );
  
  float mP[16]; nav.camera.Affine4f_Projection(mP, asp, 10);
  float mMV[16]; nav.camera.Affine4f_ModelView(mMV);
  shdr0.Draw(mP,mMV);
  
  glfwSwapBuffers(window);
  glfwPollEvents();
}

void callback_key(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
    glfwSetWindowShouldClose(window, GL_TRUE);
  }
}

void callback_resize(GLFWwindow* window, int width, int height)
{
  glViewport(0, 0, width, height);
}

void callback_mouse_button(GLFWwindow* window, int button, int action, int mods)
{
  nav.Mouse(window,button,action,mods);
  
}

void callback_cursor_position(GLFWwindow* window, double xpos, double ypos)
{
  nav.Motion(window,xpos,ypos);
}

void callback_scroll(GLFWwindow* window, double xoffset, double yoffset)
{
  nav.camera.scale *= pow(1.01,yoffset);
}


int main(void)
{
  {
    MakeMesh();
    aVal.assign(aXY1.size()/2, 0.0);
    InitializeProblem_Scalar();
    SolveProblem_Poisson();
  }
  
  GLFWwindow* window = myGLFW_OpenWindow(800,600);
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, callback_resize);
  glfwSetKeyCallback(            window, callback_key);
  glfwSetMouseButtonCallback(    window, callback_mouse_button);
  glfwSetCursorPosCallback(      window, callback_cursor_position);
  glfwSetScrollCallback(         window, callback_scroll);
  
  // glad: load all OpenGL function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  shdr0.Compile();
  shdr0.Initialize(aXY1, 2, aTri1, aVal);
  shdr0.val_min = 0.0;
  shdr0.val_max = 0.3;
    
  nav.camera.view_height = 1.5;
  nav.camera.camera_rot_mode = CAMERA_ROT_TBALL;
  
  
#ifdef EMSCRIPTEN
  emscripten_set_main_loop_arg((em_arg_callback_func) draw, window, 60, 1);
#else
  while (!glfwWindowShouldClose(window)) { draw(window); }
#endif
  
  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
