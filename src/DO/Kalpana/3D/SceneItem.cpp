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

    // Allocate the VBO with the appropriate size.
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex),
                 reinterpret_cast<void *>(_vertices.data()),
                 GL_STATIC_DRAW);

    glBindVertexArray(_vao);
    // layout(location = 0) in vec3 position;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, point)));
    // layout(location = 1) in vec3 color;
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, color)));
    // layout(location = 2) in float point_size;
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, size)));
  }

  void PointCloud::draw() const
  {
    _shader_program.use();

    // debug.
    Matrix4f mat;

    glMatrixMode(GL_PROJECTION);
    glGetFloatv(GL_PROJECTION_MATRIX, mat.data());
    glUniformMatrix4fv(glGetUniformLocation(_shader_program, "proj_mat"),
                       1, GL_FALSE, mat.data());

    glMatrixMode(GL_MODELVIEW);
    glGetFloatv(GL_MODELVIEW_MATRIX, mat.data());
    glUniformMatrix4fv(glGetUniformLocation(_shader_program, "modelview_mat"),
                       1, GL_FALSE, mat.data());
    cout << mat << endl;

    glBindVertexArray(_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawArrays(GL_POINTS, 0, _vertices.size());

    _shader_program.use(false);
  }

} /* namespace Kalpana */
} /* namespace DO */
