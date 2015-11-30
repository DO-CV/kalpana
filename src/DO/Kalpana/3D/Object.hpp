#pragma once

#include <Eigen/Core>


namespace DO { namespace Kalpana {

  using namespace Eigen;

  class Object3D
  {
  public:
    virtual ~Object3D();

    virtual void draw() const = 0;
  };


  class Histogram : public Object3D
  {
  public:
    Histogram() = default;

    Histogram(const std::vector<Vector3f>& points);

    void draw() const override;

  private:
    std::vector<Vector3f> _pos;
    std::vector<Vector3f> _col;
    std::vector<float> _sz;
  };

} /* namespace Kalpana */
} /* namespace DO */
