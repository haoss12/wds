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

    /**
     * @brief Initialization of OpenGL scene
     *
     */
    void initializeGL();
    /**
     * @brief OpenGL drawing of scene
     *
     */
    void paintGL();
    /**
     * @brief OpenGL resize event
     *
     */
    void resizeGL(int w, int h);

    /**
     * @brief Set rocket Euler angles
     *
     * @param in - angles for X, Y and Z axis
     *
     */
    void setAngles(float _x, float _y, float _z) {angX = _x; angY = _y; angZ = _z;};
    void setAngX(float _ang) {angX = _ang;};
    void setAngY(float _ang) {angY = _ang;};
    void setAngZ(float _ang) {angZ = _ang;};

    /**
     * @brief Get rocket Euler angle
     *
     * @return X axis angle
     *
     */
    float getAngX() const {return angX;};
    /**
     * @brief Get rocket Euler angle
     *
     * @return Y axis angle
     *
     */
    float getAngY() const {return angY;};
    /**
     * @brief Get rocket Euler angle
     *
     * @return Z axis angle
     *
     */
    float getAngZ() const {return angZ;};

private:
    float angX, angY, angZ;
    QTimer timer;

};

#endif // ROCKETRENDERER_H
