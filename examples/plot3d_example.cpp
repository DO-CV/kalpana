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

  auto vertex_shader = KALPANA_STRINGIZE(
    void main(void)
    {
      ;
    });
  auto fragment_shader = KALPANA_STRINGIZE(
    void main(void)
    {
    });

  point_cloud->set_vertex_shader_source(vertex_shader);
  point_cloud->set_fragment_shader_source(fragment_shader);
  point_cloud->initialize_shaders();

  ax.resize(320, 240);
  ax.show();

  return app.exec();
}
