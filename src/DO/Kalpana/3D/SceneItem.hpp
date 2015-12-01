#pragma once

#include <vector>

#include <Eigen/Core>


namespace DO { namespace Kalpana {

  using namespace Eigen;

  class SceneItem
  {
  public:
    SceneItem() = default;

    virtual ~SceneItem()
    {
    }

    virtual void draw() const = 0;
  };


  class Histogram : public SceneItem
  {
  public:
    Histogram() = default;

    Histogram(const std::vector<Vector3f>& points);

    Histogram(Histogram&& other)
      : _pos{ std::move(other._pos) }
      , _col{ std::move(other._col) }
      , _sz{ std::move(other._sz) }
    {
    }

    ~Histogram()
    {
    }

    void draw() const override;

  private:
    std::vector<Vector3f> _pos;
    std::vector<Vector3f> _col;
    std::vector<float> _sz;
  };

} /* namespace Kalpana */
} /* namespace DO */
