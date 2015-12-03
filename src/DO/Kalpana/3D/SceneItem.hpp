#pragma once

#include <vector>

#include <Eigen/Core>

#include <DO/Kalpana/3D.hpp>


namespace DO { namespace Kalpana {

  using namespace Eigen;

  class Shader;
  class ShaderProgram;

  class SceneItem
  {
  public:
    SceneItem() = default;

    virtual ~SceneItem()
    {
    }

    virtual void draw() const = 0;

    //virtual BBox bounding_box() const = 0;
  };

  class PointCloud : public SceneItem
  {
  public:
    PointCloud() = default;

    PointCloud(const std::vector<Vector3f>& points);

    PointCloud(PointCloud&& other)
      : _pos{ std::move(other._pos) }
      , _col{ std::move(other._col) }
      , _sz{ std::move(other._sz) }
    {
    }

    ~PointCloud()
    {
    }

    void set_vertex_shader_source(const std::string& source);

    void set_framgment_shader_source(const std::string& source);

    void initialize_shaders() const;

    void draw() const override;

  private:
    //! @{
    //! @brief Vertices.
    std::vector<Vector3f> _pos;
    std::vector<Vector3f> _col;
    std::vector<float> _sz;
    //! @}

    //! @{
    //! @brief Rendering properties
    Shader *_vertex_shader{ nullptr };
    Shader *_fragment_shader{ nullptr };
    ShaderProgram *_shader_program{ nullptr };
    //! @}
  };

} /* namespace Kalpana */
} /* namespace DO */
