#ifndef DO_KALPANA_CORE_CANVAS_HPP
#define DO_KALPANA_CORE_CANVAS_HPP

#include <QGraphicsView>

#include <DO/Sara/Core/EigenExtension.hpp>


namespace DO { namespace Kalpana {

  using namespace Eigen;


  class Canvas : public QGraphicsView
  {
    Q_OBJECT

  public:
    Canvas(QWidget *parent = 0);

  public slots:
    void plot(const VectorXd& x, const VectorXd& y, const QPen& pen = QPen{});

  private:
    void scaleView(qreal scaleFactor);

  protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
  };

} /* namespace Kalpana */
} /* namespace DO */

#endif /* DO_KALPANA_CORE_CANVAS_HPP */
