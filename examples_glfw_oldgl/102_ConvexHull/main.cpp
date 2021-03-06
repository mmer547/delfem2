#include <vector>
#include <cstdlib>
#include "delfem2/vec3.h"
#include "delfem2/mshmisc.h"
#include "delfem2/mshtopo.h"
#include "delfem2/primitive.h"

#include <GLFW/glfw3.h>
#include "delfem2/opengl/glfw_viewer.hpp"
#include "delfem2/opengl/gl2_funcs.h"

// ---------------------------------------

static void myGlVertex3d(const CVector3& v)
{
  ::glVertex3d(v.x,v.y,v.z);
}

static void myGlVertex3d
(unsigned int i,
 const std::vector<CVector3>& aV)
{
  const CVector3& v = aV[i];
  ::glVertex3d(v.x,v.y,v.z);
}

int main(int argc,char* argv[])
{
  delfem2::opengl::CViewer_GLFW viewer;
  viewer.Init_oldGL();
  
  viewer.nav.camera.view_height = 1.5;
  
  std::vector<CVector3> aXYZ;
  std::vector<int> aTri;
    
  while (!glfwWindowShouldClose(viewer.window))
  {
    {
      static int iframe = 0;
      if( iframe == 0 ){
        int nXYZ = 100;
        aXYZ.resize(nXYZ);
        for(int ixyz=0;ixyz<nXYZ;ixyz++){
          aXYZ[ixyz].x = 2.0*(double)rand()/(RAND_MAX+1.0)-1.0;
          aXYZ[ixyz].y = 2.0*(double)rand()/(RAND_MAX+1.0)-1.0;
          aXYZ[ixyz].z = 2.0*(double)rand()/(RAND_MAX+1.0)-1.0;
        }
        delfem2::ConvexHull(aTri,aXYZ);
      }
      iframe = (iframe + 1)%300;
    }
    
    viewer.DrawBegin_oldGL();
    
    ::glEnable(GL_BLEND);
    ::glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    ::glEnable(GL_CULL_FACE);
    ::glCullFace(GL_BACK);
    {
      ::glColor3d(0,0,0);
      ::glPointSize(3);
      ::glBegin(GL_POINTS);
      for(const auto & ixyz : aXYZ){
        myGlVertex3d(ixyz);
      }
      ::glEnd();
      
      const unsigned int nTri = aTri.size()/3;
      ::glColor4d(1,1,1,0.8);
      ::glBegin(GL_TRIANGLES);
      for(unsigned int itri=0;itri<nTri;itri++){
        const int i1 = aTri[itri*3+0];
        const int i2 = aTri[itri*3+1];
        const int i3 = aTri[itri*3+2];
        myGlVertex3d(i1,aXYZ);
        myGlVertex3d(i2,aXYZ);
        myGlVertex3d(i3,aXYZ);
      }
      ::glEnd();
      ::glColor3d(0,0,0);
      ::glBegin(GL_LINES);
      for(unsigned int itri=0;itri<nTri;itri++){
        const unsigned int i1 = aTri[itri*3+0];
        const unsigned int i2 = aTri[itri*3+1];
        const unsigned int i3 = aTri[itri*3+2];
        myGlVertex3d(i1,aXYZ);
        myGlVertex3d(i2,aXYZ);
        myGlVertex3d(i2,aXYZ);
        myGlVertex3d(i3,aXYZ);
        myGlVertex3d(i3,aXYZ);
        myGlVertex3d(i1,aXYZ);
      }
      ::glEnd();
    }
    
    glfwSwapBuffers(viewer.window);
    glfwPollEvents();
  }
  glfwDestroyWindow(viewer.window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
