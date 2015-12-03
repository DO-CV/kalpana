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

  Canvas3D ax{};
  auto point_cloud = ax.scatter(points);

  // Special configuration for 3D histogram plotting.

  // Put this in Canvas3D::initializeGL()
  auto vertex_shader = string{ R"(
    uniform mat4 gl_ModelViewProjectionMatrix;

    layout(location = 0) in vec3 position;
    layout(location = 1) in vec3 color;
    layout(location = 2) in float size;

    void main(void)
    {
      gl_Position = gl_ModelViewProjectionMatrix * vec4(position, 1.0);
      gl_Color = vec4(color, 1.0);
      gl_PointSize = size;
    })" };

  auto fragment_shader = string{ R"(
    out vec4 frag_color;

    void main(void)
    {
      frag_color = vec4(1.0, 0.0, 0.0, 1.0);
    })" };

  point_cloud->set_vertex_shader_source(vertex_shader);
  point_cloud->set_fragment_shader_source(fragment_shader);
  point_cloud->initialize_shaders();


  // Put this in Canvas3D::paintEvent()

  ax.resize(320, 240);
  ax.show();

  return app.exec();
}
