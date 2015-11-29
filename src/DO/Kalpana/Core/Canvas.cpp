#include <QtOpenGL>

#include <DO/Kalpana/Core.hpp>


namespace DO { namespace Kalpana {

  Canvas::Canvas(QWidget *parent)
    : QGraphicsView{ parent }
  {
    setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    setTransformationAnchor(AnchorUnderMouse);
    setRenderHints(QPainter::Antialiasing);
    setDragMode(RubberBandDrag);

    setScene(new QGraphicsScene);
  }

  void Canvas::plot(const VectorXd& x, const VectorXd& y, const QPen& pen)
  {
    scene()->addItem(new Graph{ x, y, pen });
    fitInView(sceneRect());
  }

  void Canvas::scaleView(qreal scaleFactor)
  {
    scale(scaleFactor, scaleFactor);
  }

  void Canvas::mousePressEvent(QMouseEvent *event)
  {
    QGraphicsView::mousePressEvent(event);
  }

  void Canvas::mouseReleaseEvent(QMouseEvent *event)
  {
    QGraphicsView::mouseReleaseEvent(event);
  }

  void Canvas::mouseMoveEvent(QMouseEvent *event)
  {
    QGraphicsView::mouseMoveEvent(event);
  }

  void Canvas::wheelEvent(QWheelEvent *event)
  {
    if (event->modifiers() == Qt::ControlModifier)
      scaleView(pow(double(2), event->delta() / 240.0));
    QGraphicsView::wheelEvent(event);
  }

  void Canvas::keyPressEvent(QKeyEvent *event)
  {
    // Adjust view.
    if (event->key() == Qt::Key_F)
      fitInView(sceneRect());

    QGraphicsView::keyPressEvent(event);
  }
} /* namespace Kalpana */
} /* namespace DO */
