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

//! @file

#ifndef DO_KALPANA_GRAPHICS_OPENGLWINDOW_HPP
#define DO_KALPANA_GRAPHICS_OPENGLWINDOW_HPP

#include <QGLWidget>

#include <Eigen/Core>

#include <DO/Kalpana/3D/Frame.hpp>
#include <DO/Kalpana/3D/Scene.hpp>
#include <DO/Kalpana/3D/SceneItem.hpp>
#include <DO/Kalpana/3D/TrackBall.hpp>


namespace DO { namespace Kalpana {

  using namespace Eigen;

  //! @brief QGLWidget-derived class used to view 3D scenes.
  class Canvas3D : public QGLWidget
  {
  public:
    Canvas3D(QWidget* parent = 0);

    PointCloud * scatter(const std::vector<Vector3f>& points);

  protected:
    void initializeGL();

    void paintEvent(QPaintEvent *event);

    void resizeGL(int width, int height);

    void mousePressEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);

    void mouseMoveEvent(QMouseEvent *event);

    void wheelEvent(QWheelEvent *event);

    void keyPressEvent(QKeyEvent *event);

    void closeEvent(QCloseEvent *event);

  protected:
    QPointF normalizePos(const QPointF& localPos) const;

  private:
    //! Modelview parameters.
    GLfloat m_scale;
    Vector3f m_center;

    //! World coordinate frame.
    Frame m_frame;
    bool m_displayFrame;

    //! The scene
    Scene m_scene;

    //! Trackball parameters for mouse-based navigation.
    TrackBall m_trackball;
    QPoint m_lastPos;

    //! Rendering parameters.
    QColor m_backgroundColor;
    QColor m_color;
  };

} /* namespace Kalpana */
} /* namespace DO */


#endif /* DO_KALPANA_GRAPHICS_OPENGLWINDOW_HPP */
