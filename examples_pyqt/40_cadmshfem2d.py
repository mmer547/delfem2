####################################################################
# Copyright (c) 2019 Nobuyuki Umetani                              #
#                                                                  #
# This source code is licensed under the MIT license found in the  #
# LICENSE file in the root directory of this source tree.          #
####################################################################

import sys, math

from PyQt5.QtCore import QSize
from PyQt5.QtWidgets import (QApplication, QVBoxLayout, QOpenGLWidget, QMenu,
                             QWidget, QPushButton)

import OpenGL.GL as gl

sys.path.append("../module_py")
import delfem2 as dfm2
import delfem2.gl
import delfem2.pyqt
import delfem2.cadmshfem


from PyQt5.QtWidgets import (QApplication, QWidget)

class Window(QWidget):
  def __init__(self):
    super(Window, self).__init__()

    self.cadmsh = dfm2.cadmshfem.CadMesh2D_Poisson(edge_length=0.05)
    self.cadmsh.add_polygon([-1, -1, +1, -1, +1, +1, -1, +1])

    self.glWidget = dfm2.pyqt.QOpenGLWidget_Cad2D()
    self.glWidget.cadobj = self.cadmsh

    self.ui_meshres = dfm2.pyqt.QUI_MeshRes(self.cadmsh)
    self.ui_meshres.func_updated = self.glWidget.update

    mainLayout = QVBoxLayout()
    mainLayout.addWidget(self.glWidget)
    mainLayout.addItem(self.ui_meshres.hl)
    self.setLayout(mainLayout)

    self.setWindowTitle("CAD_Mesh_FEM")

  def keyPressEvent(self, event):
    if event.text() == 'q':
      self.close()


if __name__ == '__main__':
  app = QApplication(sys.argv)
  window = Window()
  window.show()
  sys.exit(app.exec_())