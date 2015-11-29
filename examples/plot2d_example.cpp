#include <QApplication>

#include <DO/Kalpana/Core.hpp>


int main(int argc, char **argv)
{
  using namespace DO::Kalpana;

  QApplication app{ argc, argv };

  Canvas canvas{};
  canvas.show();

  return app.exec();
}
