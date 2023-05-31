#include "rocketrenderer.h"

#include <GL/glut.h>

RocketRenderer::RocketRenderer(QWidget *parent) :
    QOpenGLWidget(parent)
{
    this->angX = 0.0;
    this->angY = 0.0;
    this->angZ = 0.0;

    connect( &timer, SIGNAL(timeout()), this, SLOT(update()) );
    timer.start(16);
}

void RocketRenderer::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.1, 0.1, 0.1, 0.9);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    static GLfloat lightPosition[4] = { 0, 10, 0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void RocketRenderer::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt( 0,5,0,  0,0,0,  0,0,1 );
        //gluLookAt( 0,0,5,  0,0,0,  0,1,0 );

        glColor3f(1.0, 0.0, 0.0);

//        angX += 0.5;
//        angY += 0.5;
//        angZ += 0.5;

        glRotatef(angX, 1.0, 0.0, 0.0);
        glRotatef(angY, 0.0, 1.0, 0.0);
        glRotatef(angZ, 0.0, 0.0, 1.0);

        glutWireTorus(0.2, 0.4, 20, 20);
}

void RocketRenderer::resizeGL(int w, int h)
{
    glViewport(0,0, w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective( 45.0, (float)w/h, 0.01, 100.0 );
    update();
}
