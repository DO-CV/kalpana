#pragma once

#include <string>
#include <unordered_set>

#include <GL/gl.h>


namespace DO { namespace Kalpana {

  class Shader
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
    std::string _shader_source;

    // Shader management.
    static std::unordered_set<std::string> _shader_sources;
  };

  class ShaderProgram
  {
  public:
    ShaderProgram();

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

    // Shader program management.
    //static std::vector<GLuint> _shader_programs;
  };

} /* namespace Kalpana */
} /* namespace DO */