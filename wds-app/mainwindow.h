#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QList>

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
    QSerialPort *port;
    //QSerialPortInfo port_info;
    QByteArray data;
    float angX;
    float angY;
    float angZ;
    bool first;

    void read_data();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_4_pressed();

    void on_pushButton_4_released();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_pressed();

    void on_pushButton_5_released();

    void on_pushButton_3_pressed();

    void on_pushButton_3_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
