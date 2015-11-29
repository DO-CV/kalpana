#include <QApplication>

#include <DO/Sara/Core/EigenExtension.hpp>

#include <DO/Kalpana/Core.hpp>
#include <DO/Kalpana/Plot.hpp>


int main(int argc, char **argv)
{
  using namespace DO::Kalpana;

  QApplication app{ argc, argv };

  auto X = np::linspace(0, 100, 500);

  auto ax = new Canvas{};
  ax->plot(X, np::sin(X), plt::style(Qt::red, 5., "--"));
  ax->plot(X, np::cos(X), plt::style(Qt::blue, 5., "-"));

  ax->scene()->addItem(new Axis{ np::sin(X) });

  ax->show();
  return app.exec();
}
