#include <iostream>

#include <QtOpenGL>
#include <QtOpenGLExtensions>

#include <DO/Kalpana/3D.hpp>


using namespace std;


namespace DO { namespace Kalpana {

  PointCloud::PointCloud()
  {
    glGenBuffers(1, &_vbo);
    glGenVertexArrays(1, &_vao);
  }

  PointCloud::PointCloud(const vector<Vector3f>& points,
                         const vector<Vector3f>& colors,
                         const vector<float>& point_sizes)
    : PointCloud{}
  {
    _vertices.resize(points.size());
    for (size_t i = 0; i != _vertices.size(); ++i)
      _vertices[i] = { points[i], colors[i], point_sizes[i] };

    // Allocate the VBO with the appropriate size.
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), nullptr,
                 GL_STATIC_DRAW);

    glBindVertexArray(_vao);
    // layout(location = 0) in vec3 position;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, point)));
    // layout(location = 1) in vec3 color;
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, color)));
    // layout(location = 2) in float point_size;
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, size)));
  }

  PointCloud::~PointCloud()
  {
    glDeleteBuffers(1, &_vbo);
    glDeleteVertexArrays(1, &_vao);
  }

  void PointCloud::set_vertex_shader_source(const string& source)
  {
    _vertex_shader.create_from_source(GL_VERTEX_SHADER, source);
  }

  void PointCloud::set_fragment_shader_source(const string& source)
  {
    _fragment_shader.create_from_source(GL_FRAGMENT_SHADER, source);
  }

  void PointCloud::initialize_shaders()
  {
    _shader_program.attach(_vertex_shader, _fragment_shader);
    _shader_program.use();
  }

  void PointCloud::draw() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glDrawElements(GL_POINTS, _vertices.size(), GL_UNSIGNED_INT, nullptr);
  }

} /* namespace Kalpana */
} /* namespace DO */
