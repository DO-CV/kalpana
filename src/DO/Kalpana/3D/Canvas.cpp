// ========================================================================== //
// This file is part of DO-CV, a basic set of libraries in C++ for computer
// vision.
//
// Copyright (C) 2015 David Ok <david.ok8@gmail.com>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.
// ========================================================================== //

#include <stdexcept>

#include <GL/glew.h>

#ifdef __APPLE__
# include <OpenGL/GLU.h>
#else
# include <GL/glu.h>
#endif

#include <QtOpenGL>

#include <DO/Kalpana/3D.hpp>

#ifndef GL_MULTISAMPLE
# define GL_MULTISAMPLE  0x809D
#endif


using namespace std;


namespace DO { namespace Kalpana {

  bool Canvas3D::m_initGlew = false;

  Canvas3D::Canvas3D(QWidget* parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
    , m_scale(1.0f)
    , m_backgroundColor(QColor::fromCmykF(0.39, 0.39, 0.0, 0.0))
    , m_color(QColor::fromCmykF(0.40, 0.0, 1.0, 0.0))
  {
    if (!m_initGlew)
    {
      const auto err = glewInit();
      if (GLEW_OK != err)
        throw std::runtime_error{ "Failed to initialize GLEW!" };
      else
        m_initGlew = true;
    }

    setAttribute(Qt::WA_DeleteOnClose);

    // Needed to correctly mix OpenGL commands and QPainter drawing commands.
    setAutoFillBackground(false);

    m_displayFrame = false;

    show();
  }

  void Canvas3D::scatter(const vector<Vector3f>& points)
  {
    m_scene._objects.push_back(std::move(new Histogram{ points }));
  }

  void Canvas3D::initializeGL()
  {
    // Set background color
    qglClearColor(m_backgroundColor);

    glShadeModel(GL_SMOOTH);  // Enable smooth shading

    // Set up the cosmic background radiation.
    glEnable(GL_LIGHTING);    // Enable lighting
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);

    // Set up light source 0
    GLfloat light0Pos[]      = { 0.0f, 0.0f, 10.0f, 1.0f };
    GLfloat light0SpotDir[]  = { 0.0f, 0.0f,-1.0f, 1.0f };
    GLfloat diffuseLight0[]  = { 0.8f, 0.5f, 0.5f, 0.8f };
    GLfloat specularLight0[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0Pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0SpotDir);
    glEnable(GL_LIGHT0);

    // Set up color material
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glColorMaterial(GL_FRONT_AND_BACK, GL_SPECULAR);
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);
    glEnable(GL_COLOR_MATERIAL);

    // ?
    glEnable(GL_MULTISAMPLE);

    // Normalize the vector for the lighting
    glEnable(GL_NORMALIZE);
  }

  static void multMatrix(const QMatrix4x4& m)
  {
    // static to prevent glMultMatrixf to fail on certain drivers
    static GLfloat mat[16];
    const float *data = m.constData();
    for (int index = 0; index < 16; ++index)
      mat[index] = data[index];
    glMultMatrixf(mat);
  }

  void Canvas3D::paintEvent(QPaintEvent *)
  {
    makeCurrent();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setup the viewing mode for the mesh
    glPolygonMode(GL_FRONT, GL_FILL); // we make each front face filled
    glPolygonMode(GL_BACK, GL_LINE);  // we draw only the edges of the back face
    glEnable(GL_DEPTH_TEST);  // For depth consistent drawing

    // Model-view transform.
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -15.0f);

    // The world frame is at z=-15 w.r.t. the camera frame.
    //
    // Scale the model
    glScalef(m_scale, m_scale, m_scale);
    // Rotate the model with the trackball.
    auto m = QMatrix4x4{};
    m.rotate(m_trackball.rotation());
    multMatrix(m);
    // Display the mesh.
    glPushMatrix();
    {
      // Center the model
      glTranslatef(-m_center.x(), -m_center.y(), -m_center.z());
      // Draw the model
      for (const auto& object : m_scene._objects)
        object->draw();
    }
    glPopMatrix();

    // Object-centered frame.
    if (m_displayFrame)
      m_frame.draw(5, 0.1);

    // Disable the following to properly display the drawing with QPainter.
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    // ====================================================================== //
    // Display text overlay.
    QPainter p{ this };
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::TextAntialiasing);

    QString text = tr(
      "Use the mouse wheel to zoom and the mouse left button to rotate the scene.\n"
      "Hit 'F' to toggle object-centered frame display");
    // Set the font style
    setFont(QFont("Helvetica [Cronyx]", 10, QFont::Bold));

    // Draw the bounding box within which the text will be drawn.
    QFontMetrics metrics = QFontMetrics(font());
    const auto border = qMax(4, metrics.leading());
    QRect rect = metrics.boundingRect(
      0, 0, width() - 2*border, int(height()*0.125),
      Qt::AlignCenter | Qt::TextWordWrap, text);
    p.fillRect(QRect(0, 0, width(), rect.height() + 2*border),
               QColor(0, 0, 0, 127));

    // Draw the text.
    p.setPen(Qt::white);
    p.fillRect(QRect(0, 0, width(), rect.height() + 2*border),
               QColor(0, 0, 0, 127));
    p.setFont(font());
    p.drawText((width() - rect.width())/2, border,
               rect.width(), rect.height(),
               Qt::AlignCenter | Qt::TextWordWrap, text);
    p.end();
  }

  void Canvas3D::resizeGL(int width, int height)
  {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    const auto ratio = width/static_cast<double>(height);
    gluPerspective(60.0, ratio, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
  }

  QPointF Canvas3D::normalizePos(const QPointF& localPos) const
  {
    QPointF pos(localPos);
    pos.rx() -=  width()/2.; pos.rx() /= width()/2.;
    pos.ry() -= height()/2.; pos.ry() /= height()/2.; pos.ry() *= -1;
    return pos;
  }

  void Canvas3D::mousePressEvent(QMouseEvent *event)
  {
    QGLWidget::mousePressEvent(event);
    if (event->isAccepted())
      return;

    QPointF pos(normalizePos(event->localPos()));
    if (event->buttons() & Qt::LeftButton) {
      m_trackball.push(pos, m_trackball.rotation());
      event->accept();
    }
    update();
  }

  void Canvas3D::mouseReleaseEvent(QMouseEvent *event)
  {
    QGLWidget::mouseReleaseEvent(event);
    if (event->isAccepted())
      return;

    QPointF pos(normalizePos(event->localPos()));
    if (event->button() == Qt::LeftButton) {
      m_trackball.release(pos);
      event->accept();
    }
    update();
  }

  void Canvas3D::mouseMoveEvent(QMouseEvent *event)
  {
    QGLWidget::mouseMoveEvent(event);
    if (event->isAccepted())
    {
      qDebug() << "mouse move event already accepted";
      return;
    }

    QPointF pos(normalizePos(event->localPos()));
    if (event->buttons() & Qt::LeftButton) {
      m_trackball.move(pos);
      event->accept();
    } else {
      m_trackball.release(pos);
    }
    update();
  }

  void Canvas3D::wheelEvent(QWheelEvent* event)
  {
    QGLWidget::wheelEvent(event);

    if (!event->isAccepted()) {
      event->delta() > 0 ? m_scale += 0.05f*m_scale : m_scale -= 0.05f*m_scale;
      update();
    }
  }

  void Canvas3D::keyPressEvent(QKeyEvent *event)
  {
    if (event->key() == Qt::Key_F)
    {
      m_displayFrame=!m_displayFrame;
      update();
    }
  }

  void Canvas3D::closeEvent(QCloseEvent *event)
  {
    if(event->spontaneous())
    {
      qWarning() << "\n\nWarning: you closed a window unexpectedly!\n\n";
      qWarning() << "Graphical application is terminating...";
      qApp->exit(0);
    }
  }

} /* namespace Kalpana */
} /* namespace DO */
