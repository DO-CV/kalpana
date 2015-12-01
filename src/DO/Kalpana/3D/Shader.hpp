#pragma once

#include <stdexcept>
#include <fstream>

#include <DO/Sara/Core/StringFormat.cpp>

#include <GL/glew.h>


namespace DO { namespace Kalpana {

  class Shader
  {
  public:
    Shader() = default;

    Shader(GLenum shader_type, const std::string& filepath);

    ~Shader()
    {
      clear();
    }

    operator GLuint() const
    {
      return _shader_object;
    }

  protected:
    void create_from_source(GLenum shader_type, const std::string& source)
    {
      _shader_type = shader_type;
      _shader_object = glCreateShader(shader_type);

      _shader_source = source;
      auto shader_src_data = reinterpret_cast<const GLchar *>(_shader_source.data());
      auto shader_src_sz = static_cast<GLint>(_shader_source.size());

      glShaderSource(_shader_object, 1, &shader_src_data, &shader_src_sz);
      glCompileShader(_shader_object);

      auto err = GLint{};
      glGetObjectParameteriv(_shader_object, GL_COMPILE_STATUS, &err);
      if (GL_FALSE == err)
      {
        auto log_max_sz = GLint{ 0 };
        auto log_sz = GLsizei{ 0 };
        auto log = std::string{};

        glGetShaderiv(_shader_object, GL_INFO_LOG_LENGTH, &log_max_sz);
        if (log_sz > 1)
        {
          log.resize(log_max_sz);
          auto log_data = &log[0];
          glGetInfoLogARB(_shader_object, log_max_sz, &log_sz, log_data);
          log.resize(log_sz);
        }

        throw std::runtime_error{
          Sara::format("Error: failed to create program from source:\n%s.\n"
                       "Compilation log:\n%s", source.c_str(), log.c_str())
        };
      }
    }

    void create_from_file(GLenum shader_type, const std::string& filepath)
    {
      // Read source fle.
      std::ifstream file(filepath.c_str());
      if (!file.is_open())
        throw std::runtime_error(Sara::format(
            "Error: cannot open file: %s", filepath.c_str()));

      std::string source;
      file.seekg(0, std::ios::end);
      source.reserve(file.tellg());

      file.seekg(0, std::ios::beg);
      source.assign(std::istreambuf_iterator<char>(file),
                    std::istreambuf_iterator<char>());

      create_from_source(shader_type, source);
    }

    void clear()
    {
      if (_shader_object)
        glDeleteShader(_shader_object);

      auto err = GLint{};
      glGetShaderiv(_shader_object, GL_DELETE_STATUS, &err);
      if (GL_FALSE == err)
        throw std::runtime_error{
          Sara::format("Error: failed to delete shader: %d.", err)
        };
    }

  private:
    GLenum _shader_type;
    GLuint _shader_object{ 0 };
    std::string _shader_source;
  }

  class ShaderProgram
  {
  public:
    ShaderProgram() = default;

    ShaderProgram(const Shader& vertex_shader, const Shader& fragment_shader)
    {
      create();
      attach(vertex_shader, fragment_shader);
    }

    ~ShaderProgram()
    {
      glDetachShader(_program_object, _vertex_shader);
      glDetachShader(_program_object, _fragment_shader);
    }

    void attach(const Shader& vertex_shader, const Shader& fragment_shader)
    {
      glAttachShader(_program_object, vertex_shader);
      glAttachShader(_program_object, fragment_shader);
      glLinkProgram(_program_object);

      auto err = GLint{};
      glGetProgramiv(_program_object, GL_LINK_STATUS, &err);
      if (GL_FALSE == err)
        throw std::runtime_error{
          Sara::format("Failed to link shader program: %d", err)
        };
    }

    void use()
    {
      glUseProgram(_program_object);
    }

  protected:
    void create()
    {
      if (_program_object)
        glCreateProgram();

      if (!_program_object)
        throw std::runtime_error{ "Failed to create program!" };
    }

    void clear()
    {
      if (_program_object)
      {
        glDeleteProgram(_program_object);
        auto err = GLint{};
        glGetProgramiv(_program_object, GL_DELETE_STATUS, &err);
        if (GL_FALSE == err)
          throw std::runtime_error{ "Failed to delete program!" };
      }
      _program_object = 0;
    }

  private:
    GLuint _program_object{ 0 };
    GLuint _vertex_shader{ 0 };
    GLuint _fragment_shader{ 0 };
  };

} /* namespace Kalpana */
} /* namespace DO */
