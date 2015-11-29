#ifndef DO_KALPANA_CORE_GRAPH_HPP
#define DO_KALPANA_CORE_GRAPH_HPP

#include <DO/Sara/Core/EigenExtension.hpp>


namespace DO { namespace Kalpana {

  struct Marker
  {
    char style;
    int size;
  };

  struct Point
  {
    Marker marker;
  };

  class Graph
  {
    QVector<QPointF> lines;
  };

} /* namespace Kalpana */
} /* namespace DO */


#endif /* DO_KALPANA_CORE_GRAPH_HPP */
