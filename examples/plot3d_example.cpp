#include <QApplication>

#include <DO/Kalpana.hpp>


int main(int argc, char **argv)
{
  using namespace DO::Kalpana;

  QApplication app{ argc, argv };

  auto X = np::linspace(-6.28, 6.28, 50);

  auto ax = new Canvas3D{};
  ax->resize(320, 240);

  ax->show();
  return app.exec();
}
