import sys
sys.path.append("../module_py")
import dfm2

def main():
  msh = dfm2.Mesh()
  msh.read("../test_inputs/bunny_2k.ply")
  msh.color_face = [1,1,1,1]

  aabb = dfm2.AABB3( msh.minmax_xyz() )
  axis = dfm2.AxisXYZ(100.0)
  axis.line_width=3

  sampler = dfm2.GPUSampler()
  sampler.init(size_res_width=256,size_res_height=256,   format_color="4byte",is_depth=True)
  sampler.set_coordinate(len_grid=0.2, depth_max=100.0,
                       org=[0, -50, 0], dir_prj=[0, -1.0, 0], dir_width=[1, 0, 0])  
  sampler.color = [0,0,1,1]
  sampler.len_axis = 10
  sampler.bgcolor = [1,1,0,1]

  buffer = dfm2.DepthColorBuffer(win_size=[512,512],format_color="4byte",is_depth=True)
  buffer.start()
  sampler.start()
  msh.draw()
  sampler.end()
  buffer.close()

#  np_depth = numpy.array(dfm2.depth_buffer(sampler),copy=True)
#  print(np_depth.shape)
#  numpy.savetxt("hoge.txt",np_depth)

  dfm2.winDraw3d([msh,aabb,sampler,axis])

if __name__ == "__main__":
  main()