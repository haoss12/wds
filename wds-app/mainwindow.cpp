#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QDateTime>
#include <sstream>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->port = new QSerialPort(this);
    ui->openGLWidget->hide();
    ui->pushButton->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
//    ui->tableWidget->setRowCount(6);
//    ui->tableWidget->setColumnCount(3);
//    QStringList labels;
//    labels << "Typ" << "Odczyt" << "Jednostka";
//    ui->tableWidget->setHorizontalHeaderLabels(labels);
//    ui->tableWidget->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    QPushButton *another = qobject_cast<QPushButton *>(ui->pushButton_2);
    another->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}


void MainWindow::on_pushButton_2_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    QPushButton *another = qobject_cast<QPushButton *>(ui->pushButton);
    another->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}

#define ACC_SENSITIVITY  0.0061
#define GYRO_SENSITIVITY 0.0175
#define ALPHA 0.6
#define DT 0.2

void MainWindow::read_data()
{
    while (this->port->canReadLine()) {
        if (this->first == false) {
            QString line = this->port->readLine();
            //std::string temp;
            ui->textEdit->append(line);
            if (data.parseData(line)) {

                float accX = (float)data.getAcc(0) * ACC_SENSITIVITY;
                float accY = (float)data.getAcc(1) * ACC_SENSITIVITY;
                float accZ = (float)data.getAcc(2) * ACC_SENSITIVITY;

                float gyroX = data.getGyro(0) * GYRO_SENSITIVITY * DT;
                float gyroY = data.getGyro(1) * GYRO_SENSITIVITY * DT;
                float gyroZ = data.getGyro(2) * GYRO_SENSITIVITY * DT;

                float accAngX = (float)((atan2(accY, accZ)) + M_PI ) * (180 / M_PI);
                float accAngY = (float)((atan2(accZ, accX)) + M_PI ) * (180 / M_PI);

                this->angX = ALPHA * (gyroX * DT + this->angX) + (1.0f - ALPHA) * accAngX;
                this->angY = ALPHA * (gyroY * DT + this->angY) + (1.0f - ALPHA) * accAngY;
                this->angZ = (ALPHA * (gyroZ * DT) + this->angZ);

                if (abs(this->angY) > 400) {
                    this->angY = 0.0f;
                }

                ui->label_x_axis->setText(QString::number(this->angX) + " stopni");
                ui->label_y_axis->setText(QString::number(this->angY - 90.0f) + " stopni");
                ui->label_z_axis->setText(QString::number(this->angZ) + " stopni\r\n");

                qDebug() << this->angX << this->angY << this->angZ;
            }
        }
      else if (this->first == true)
        {
            this->first = false;
        }
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    // Output debug message and status message
    qDebug() << "Trwa szukanie urządzeń...";
    ui->textEdit->append("Trwa szukanie urządzeń...");

    // Get a list of available serial port devices
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    // Set the background color of the combo box based on whether devices were found
    if (devices.count() != 0) {
        ui->comboBox->setStyleSheet("color: rgb(0, 0, 0); background: rgb(255, 213, 1); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    }
    else {
        ui->comboBox->setStyleSheet("color: rgb(0, 0, 0); background: rgb(168, 13, 16); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
        qDebug() << "Żadne urządzenie nie zostało wykryte";
        ui->textEdit->append("Żadne urządzenie nie zostało wykryte");
    }

    // Clear the combo box and populate it with the names of the available devices
    ui->comboBox->clear();
    ui->comboBox->clear();
    for(int i = 0; i < devices.count(); i++) {
      QString str = devices.at(i).portName();
      qDebug() << str;
      ui->comboBox->addItem(str);
      ui->textEdit->append("Znaleziono: " + str);
    }
}


void MainWindow::on_pushButton_4_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}


void MainWindow::on_pushButton_4_released()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}



void MainWindow::on_pushButton_5_clicked()
{
    if (ui->comboBox->count() == 0) {
        ui->textEdit->append("Nie można połączyć - brak wykrytych urządzeń!");
        return;
    }
    if(!port->isOpen()) {
    QString portName = ui->comboBox->currentText().split(" ").first();

    this->port->setPortName(portName);

    if(port->open(QSerialPort::ReadOnly)) {
      this->port->setBaudRate(QSerialPort::Baud115200);
      this->port->setDataBits(QSerialPort::Data8);
      this->port->setParity(QSerialPort::NoParity);
      this->port->setStopBits(QSerialPort::OneStop);
      this->port->setFlowControl(QSerialPort::NoFlowControl);
      connect(port, &QSerialPort::readyRead, this, &MainWindow::read_data);
      this->angX = 0.0f;
      this->angY = 0.0f;
      this->angZ = 0.0f;
      this->first = true;
      ui->textEdit->append("Otwarcie portu szeregowego się udało!");
      ui->comboBox->setStyleSheet("color: rgb(0, 0, 0); background: rgb(34, 139, 34); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");

    } else {
      ui->textEdit->append("Otwarcie portu szeregowego się nie udało!");
    }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(port->isOpen()) {
        this->port->close();
        ui->textEdit->append("Zamknięto port!");
        ui->comboBox->clear();
        ui->comboBox->setStyleSheet("color: rgb(0, 0, 0); background: rgb(168, 13, 16); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    }
    else {
        ui->textEdit->append("Port nie jest otwarty!");
        return;
    }
}


void MainWindow::on_pushButton_5_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}


void MainWindow::on_pushButton_5_released()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}


void MainWindow::on_pushButton_3_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}


void MainWindow::on_pushButton_3_released()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}

