#pragma once

#include <string>

#include <QOpenGLFunctions_4_3_Core>


namespace DO { namespace Kalpana {

  class Shader : protected QOpenGLFunctions_4_3_Core
  {
  public:
    Shader() = default;

    ~Shader();

    operator GLuint() const { return _shader_object; }

    void create_from_source(GLenum shader_type, const std::string& source);

    void create_from_file(GLenum shader_type, const std::string& filepath);

  private:
    void clear();

  private:
    GLenum _shader_type;
    GLuint _shader_object{ 0 };
  };

  class ShaderProgram : protected QOpenGLFunctions_4_3_Core
  {
  public:
    ShaderProgram() = default;

    ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader);

    ~ShaderProgram();

    operator GLuint() const { return _program_object; }

    void attach(const Shader& vertex_shader, const Shader& fragment_shader);

    void detach();

    void use(bool on = true);

  protected:
    void create();

    void clear();

  private:
    GLuint _program_object{ 0 };
    GLuint _vertex_shader{ 0 };
    GLuint _fragment_shader{ 0 };
  };

} /* namespace Kalpana */
} /* namespace DO */
