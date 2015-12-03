#pragma once

#include <vector>

#include <GL/gl.h>

#include <Eigen/Core>

#include <DO/Kalpana/3D/Shader.hpp>
#include <DO/Kalpana/3D.hpp>


namespace DO { namespace Kalpana {

  using namespace Eigen;

  class SceneItem
  {
  public:
    SceneItem() = default;

    virtual ~SceneItem() {}

    virtual void draw() const = 0;

    //virtual BBox bounding_box() const = 0;
  };

  class PointCloud : public SceneItem
  {
    struct Vertex
    {
      Vector3f point;
      Vector3f color;
      float size;
    };

  public:
    PointCloud();

    PointCloud(const std::vector<Vector3f>& points,
               const std::vector<Vector3f>& colors,
               const std::vector<float>& sz);

    ~PointCloud();

    void set_vertex_shader_source(const std::string& source);

    void set_fragment_shader_source(const std::string& source);

    void initialize_shaders();

    void draw() const override;

  private:
    //! @brief Vertex data in host memory.
    std::vector<Vertex> _vertices;

    //! @{
    //! @brief Vertex data in device memory.
    GLuint _vbo = { 0 };
    GLuint _vao = { 0 };
    //! @}

    //! @{
    //! @brief Rendering properties
    Shader _vertex_shader;
    Shader _fragment_shader;
    ShaderProgram _shader_program;
    //! @}
  };

} /* namespace Kalpana */
} /* namespace DO */
