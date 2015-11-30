#include <GL/glew.h>

#include <DO/Kalpana/3D.hpp>


using namespace std;


namespace DO { namespace Kalpana {

  Histogram(const std::vector<Vector3f>& points)
    _pos{ points }
  {
    _col.resize(points.size());
    fill(_col.begin(), _col.end(), Vector3f::Ones());

    _sz.resize(points.size());
    fill(_sz.begin(), _sz.end(), 2.f);
  }

  void Histogram::draw() const
  {
    glBegin(GL_POINTS);
    {
      glVertex3fv(reinterpret_cast<const float *>(_pos.data()));
      glColor3fv(reinterpret_cast<const float *>(_col.data()));
      glPointParameterfv(GL_POINT_FADE_THRESHOLD_SIZE, _sz.data());
    }
    glEnd();
  }

} /* namespace Kalpana */
} /* namespace DO */
