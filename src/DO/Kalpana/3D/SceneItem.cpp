#include <iostream>

#include <GL/glew.h>

#include <DO/Kalpana/3D.hpp>


using namespace std;


namespace DO { namespace Kalpana {

  Histogram::Histogram(const vector<Vector3f>& points)
    : _pos{ points }
  {
    _col.resize(points.size());
    fill(_col.begin(), _col.end(), Vector3f::Ones());

    _sz.resize(points.size());
    fill(_sz.begin(), _sz.end(), 2.f);
  }

  void Histogram::draw() const
  {
    const auto *pos_arr = reinterpret_cast<const float *>(_pos.data());
    const auto *col_arr = reinterpret_cast<const float *>(_col.data());
    const auto *sz_arr = reinterpret_cast<const float *>(_sz.data());

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glPointSize(5.);
    {
      glVertexPointer(3, GL_FLOAT, 0, pos_arr);
      glColorPointer(3, GL_FLOAT, 0, col_arr);
      glDrawArrays(GL_POINTS, 0, _pos.size());
    }
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }

} /* namespace Kalpana */
} /* namespace DO */
