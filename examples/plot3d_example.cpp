#include <QApplication>

#include <DO/Kalpana.hpp>


int main(int argc, char **argv)
{
  using namespace std;
  using namespace DO::Kalpana;

  QApplication app{ argc, argv };

  vector<Vector3f> points;
  for (int i = 0; i < 10; ++i)
    points.push_back(Vector3f(i, i, i));

  Canvas3D ax{};
  ax.scatter(points);

  ax.resize(320, 240);
  ax.show();

  return app.exec();
}
