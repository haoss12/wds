#ifndef ROCKETRENDERER_H
#define ROCKETRENDERER_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>

class RocketRenderer : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    /**
     * @brief Default RocketRenderer constructor
     *
     */
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
     * @param[in] - angles for X, Y and Z axis in degrees
     *
     */
    void setAngles(float _x_deg, float _y_deg, float _z_deg) {angX = _x_deg; angY = _y_deg; angZ = _z_deg;};
    /**
     * @brief Set rocket Euler angle
     *
     * @param[in] - angles for X axis in degrees
     *
     */
    void setAngX(float _ang) {angX = _ang;};
    /**
     * @brief Set rocket Euler angle
     *
     * @param[in]  - angles for X axis in degrees
     *
     */
    void setAngY(float _ang) {angY = _ang;};
    /**
     * @brief Set rocket Euler angle
     *
     * @param[in] - angles for X axis in degrees
     *
     */
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
    float angX, angY, angZ; /**< X, Y and Z axis angle */
    QTimer timer; /**< Timer for refreshing scene */

};

#endif // ROCKETRENDERER_H
