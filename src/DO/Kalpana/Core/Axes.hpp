#ifndef DO_KALPANA_CORE_AXES_HPP
#define DO_KALPANA_CORE_AXES_HPP

#include <DO/Sara/Core/EigenExtension.hpp>

#include <QGraphicsPolygonItem>
#include <QPen>


namespace DO { namespace Kalpana {

  using namespace Eigen;

  class Axis : public QGraphicsItem
  {
  public:
    Axis()
      : m_pen{ Qt::black, 1. }
    {
      m_pen.setCosmetic(true);
    }

    Axis(const VectorXd& range);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    QRectF boundingRect() const;

  private:
    QVector<QPointF> m_ticks;
    double m_delta;
    QPen m_pen;
  };

} /* namespace Kalpana */
} /* namespace DO */


#endif /* DO_KALPANA_CORE_AXES_HPP */
