#include <iostream>

#include <QtOpenGL>
#include <QtOpenGLExtensions>

#include <DO/Kalpana/3D.hpp>


using namespace std;


namespace DO { namespace Kalpana {

  SceneItem::~SceneItem()
  {
    clear();
  }

  void SceneItem::set_vertex_shader_source(const string& source)
  {
    _vs_source = source;
  }

  void SceneItem::set_fragment_shader_source(const string& source)
  {
    _fs_source = source;
  }

  void SceneItem::clear()
  {
    if (_vbo)
    {
      glDeleteBuffers(1, &_vbo);
      _vbo = 0;
    }

    if (_vao)
    {
      glDeleteVertexArrays(1, &_vao);
      _vao = 0;
    }
  }

  void SceneItem::initialize_shaders()
  {
    _vertex_shader.create_from_source(GL_VERTEX_SHADER, _vs_source);
    _fragment_shader.create_from_source(GL_FRAGMENT_SHADER, _fs_source);

    _shader_program.attach(_vertex_shader, _fragment_shader);
  }

  PointCloud::PointCloud(const vector<Vector3f>& points,
                         const vector<Vector3f>& colors,
                         const vector<float>& point_sizes)
  {
    _vertices.resize(points.size());
    for (size_t i = 0; i != _vertices.size(); ++i)
      _vertices[i] = { points[i], colors[i], point_sizes[i] };
  }

  void PointCloud::initialize()
  {
    clear();
    initialize_shaders();

    glGenBuffers(1, &_vbo);
    glGenVertexArrays(1, &_vao);

    // Copy the vertex data to the VBO.
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex),
                 reinterpret_cast<void *>(_vertices.data()),
                 GL_STATIC_DRAW);
  }

  void PointCloud::draw() const
  {
    _shader_program.use();

    Matrix4f mat;

    glMatrixMode(GL_PROJECTION);

    // Create method for Shader program to set data to shader.
    glGetFloatv(GL_PROJECTION_MATRIX, mat.data());
    auto proj_mat = glGetUniformLocation(_shader_program, "proj_mat");
    if (GL_INVALID_VALUE == proj_mat || GL_INVALID_OPERATION == proj_mat)
      throw runtime_error{ "Invalid shader program" };
    glUniformMatrix4fv(proj_mat, 1, GL_FALSE, mat.data());

    glMatrixMode(GL_MODELVIEW);
    glGetFloatv(GL_MODELVIEW_MATRIX, mat.data());
    auto modelview_mat = glGetUniformLocation(_shader_program, "modelview_mat");
    if (GL_INVALID_VALUE == modelview_mat || GL_INVALID_OPERATION == modelview_mat)
      throw runtime_error{ "Invalid shader program" };
    glUniformMatrix4fv(modelview_mat, 1, GL_FALSE, mat.data());

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBindVertexArray(_vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, point)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, color)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, size)));

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glDrawArrays(GL_POINTS, 0, _vertices.size());

    _shader_program.use(false);
  }

} /* namespace Kalpana */
} /* namespace DO */
