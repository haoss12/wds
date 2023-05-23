#ifndef ROCKETRENDERER_H
#define ROCKETRENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class RocketRenderer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    RocketRenderer(QWidget *parent = 0);

    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    float ang;
    QTimer timer;

};

#endif // ROCKETRENDERER_H
