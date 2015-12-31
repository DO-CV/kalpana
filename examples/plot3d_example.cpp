#include <map>

#include <QApplication>

#include <DO/Kalpana.hpp>


int main(int argc, char **argv)
{
  using namespace std;
  using namespace DO::Kalpana;

  QApplication app{ argc, argv };

  vector<Vector3f> points;
  for (int i = -10; i < 10; ++i)
    points.push_back(Vector3f(i, i, i));

  Scene scene{};

  auto point_cloud = scene.scatter(points);

  // Put this in Canvas3D::initializeGL()
  auto vertex_shader = string{ R"(
    #version 450

    uniform mat4 proj_mat;
    uniform mat4 modelview_mat;

    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 color;
    layout(location = 2) in float size;

    void main(void)
    {
      gl_Position = proj_mat * modelview_mat * vec4(position, 1.0);
      //gl_Color = vec4(color, 1.0);
      gl_PointSize = abs(position[2]);
    })" };

  auto fragment_shader = string{ R"(
    void main(void)
    {
      gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    })" };

  point_cloud->set_vertex_shader_source(vertex_shader);
  point_cloud->set_fragment_shader_source(fragment_shader);


  // Put this in Canvas3D::paintEvent()
  Canvas3D ax{ &scene };
  ax.resize(320, 240);
  ax.show();

  return app.exec();
}
