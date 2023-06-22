#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QList>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts>
#include "dataframe.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QSerialPort *port;  /**< Pointer to the serial port */
    dataFrame data; /**< Data frame to parse info from serial port*/
    float angX; /**< X axis angle */
    float angY; /**< Y axis angle */
    float angZ; /**< Z axis angle */
    float counter; /**< Counter for plot */
    bool first; /**< Flag to indicate if it is the first data to read after opening port */
    QGraphicsScene *scene, *gyro_icon_scene, *acc_icon_scene, *rocket_icon_scene; /**< Scenes for drawing items */
    QGraphicsPixmapItem *fin1, *fin2, *fin3, *fin4, *acc_icon, *gyro_icon, *rocket_icon; /**< Pixmaps for items */
    QLineSeries *series; /**< Series for plot */
    QChart *chart; /**< Chart pointer */
    QChartView *chart_view; /**< Chart view object */
    QVBoxLayout *layout; /**< Layout to scale chart */
    QValueAxis *axis_x; /**< X Axis scale */

    /**
     * @brief Reads and processes data from the port
     */
    void read_data();


    /**
     * @brief Add new data to angle chart
     *
     * @param in - data to put into chart
     */
    void add_to_chart(const float &data);

private slots:

    /**
     * @brief Change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_clicked();

    /**
     * @brief Change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_2_clicked();

    /**
     * @brief Searches for available serial port devices and populates a combo box with their names.
     *
     * It also sets the background color of the combo box depending on whether
     * any devices were found. If devices were found, the background color is set to yellow; otherwise, it is set
     * to red.
     *
     * @note This function is triggered when the user clicks the "Search for Devices" button in the user interface.
     * @note This function assumes that the combo box and text edit widgets have already been initialized in the user interface.
     * @note This block of documentation was generated by ChatGPT
     */
    void on_pushButton_4_clicked();

    /**
     * @brief Connects with port selected in combo box and set its parameters.
     */
    void on_pushButton_5_clicked();

    /**
     * @brief If the port is open, close it and clear the combo box. Change the background color
     * of combo box to red. If the port is not open, print a message to user.
     */
    void on_pushButton_3_clicked();

    /**
     * @brief Change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_4_pressed();

    /**
     * @brief Change style sheet of the button when its released.
    */
    void on_pushButton_4_released();

    /**
     * @brief Change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_5_pressed();

    /**
     * @brief Change style sheet of the button when its released.
    */
    void on_pushButton_5_released();

    /**
     * @brief Change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_3_pressed();

    /**
     * @brief Change style sheet of the button when its released.
    */
    void on_pushButton_3_released();

    /**
     * @brief Test rotation of the fins
    */
    void on_pushButton_6_clicked();

    /**
     * @brief Change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_6_pressed();

    /**
     * @brief Change style sheet of the button when its released.
    */
    void on_pushButton_6_released();

    /**
     * @brief Change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_7_pressed();

    /**
     * @brief Change style sheet of the button when its released.
    */
    void on_pushButton_7_released();

    /**
     * @brief Change application language to polish, also change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_8_clicked();

    /**
     * @brief Change application language to english, also change style sheet of the button when its pressed to make it highlighted.
    */
    void on_pushButton_9_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
