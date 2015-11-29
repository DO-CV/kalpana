#include <utility>

#include <DO/Kalpana/Core.hpp>


namespace DO { namespace Kalpana {

  Axis::Axis(const VectorXd& range)
    : Axis{}
  {
    auto a = range.minCoeff();
    auto b = range.maxCoeff();

    m_ticks.resize(11);
    for (int i = 0; i < 11; ++i)
      m_ticks[i] = QPointF{ 0, a + (b-a) * i / 10 };

    m_delta = (m_ticks.back().y() - m_ticks.front().y())*5e-2;
  }

  void Axis::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                   QWidget *widget)
  {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(m_pen);
    painter->setOpacity(0.5);

    painter->drawLine(QLineF{ m_ticks.front(), m_ticks.back() });
    for (int i = 1; i < 10; ++i)
      painter->drawLine(
        QLineF{ -m_delta/2, m_ticks[i].y(), m_delta/2, m_ticks[i].y() });
  }

  QRectF Axis::boundingRect() const
  {
    return QRectF{ -m_delta, m_ticks.front().y(), m_delta, m_ticks.back().y() };
  }

} /* namespace Kalpana */
} /* namespace DO */
