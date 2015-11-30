#pragma once

#include <Eigen/Core>


namespace DO { namespace Kalpana {

  using namespace Eigen;

  class Object3D
  {
  public:
    virtual void draw() = 0;
  };

  class Vertex : public Object3D
  {
  public:
    void draw() override;

  private:
    Vector3f _pos;
    Vector3f _col;
    float _sz;
  };

  class Histogram : public Object3D
  {
  public:
    Histogram() = default;

    void draw() override;

  private:
    std::vector<Vertex> _bins;
  }


} /* namespace Kalpana */
} /* namespace DO */
