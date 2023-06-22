#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QDebug>
#include <QDateTime>
#include <QChar>
#include <QThread>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts>
#include <sstream>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->port = new QSerialPort(this);
    ui->openGLWidget->hide();
    ui->chart_frame->hide();
    ui->pushButton->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    ui->label->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_2->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_6->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_10->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_5->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_8->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_14->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_12->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
    ui->label_16->setAlignment(Qt::AlignVCenter | Qt::AlignRight);
//    ui->label_x_axis->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
//    ui->label_y_axis->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
//    ui->label_z_axis->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    scene = new QGraphicsScene(this);
    this->fin2 = new QGraphicsPixmapItem(QPixmap("/home/hubert/wds/wds-app/assets/fin.png"));
    this->fin2->setScale(0.5);
    this->fin2->setTransformOriginPoint(150, 150);
    this->scene->addItem(this->fin2);
    this->fin1 = this->scene->addPixmap(QPixmap("/home/hubert/wds/wds-app/assets/fin.png"));
    this->fin1->setScale(0.5);
    this->fin1->setTransformOriginPoint(150, 150);
    this->fin1->setPos(200, 200);
    this->fin3 = this->scene->addPixmap(QPixmap("/home/hubert/wds/wds-app/assets/fin.png"));
    this->fin3->setScale(0.5);
    this->fin3->setTransformOriginPoint(150, 150);
    this->fin3->setPos(200, 0);
    this->fin4 = this->scene->addPixmap(QPixmap("/home/hubert/wds/wds-app/assets/fin.png"));
    this->fin4->setScale(0.5);
    this->fin4->setTransformOriginPoint(150, 150);
    this->fin4->setPos(0, 200);
    ui->graphicsView->setScene(scene);

    gyro_icon_scene = new QGraphicsScene(this);
    this->gyro_icon = this->gyro_icon_scene->addPixmap(QPixmap("/home/hubert/wds/wds-app/assets/gyro_.png"));
    this->gyro_icon->setScale(0.7);
    this->gyro_icon->setTransformOriginPoint(50, 50);
    ui->graphicsView_gyro_icon->setScene(gyro_icon_scene);

    acc_icon_scene = new QGraphicsScene(this);
    this->acc_icon = this->acc_icon_scene->addPixmap(QPixmap("/home/hubert/wds/wds-app/assets/acc_.png"));
    this->acc_icon->setScale(0.7);
    this->acc_icon->setTransformOriginPoint(50, 50);
    ui->graphicsView_acc_icon->setScene(acc_icon_scene);

    rocket_icon_scene = new QGraphicsScene(this);
    this->rocket_icon = this->rocket_icon_scene->addPixmap(QPixmap("/home/hubert/wds/wds-app/assets/rocket_.png"));
    this->rocket_icon->setScale(0.7);
    this->rocket_icon->setTransformOriginPoint(50, 50);
    ui->graphicsView_axis_icon->setScene(rocket_icon_scene);

    counter = 0.0f;

    series = new QLineSeries();
    this->series->append(counter, -60.0f);
    counter += 1.0f;
    *series << QPointF(counter, 360.0f);
    counter += 1.0f;
    this->chart = new QChart();
    this->chart->legend()->hide();
    this->chart->createDefaultAxes();
    QValueAxis *axis_y = new QValueAxis();
    axis_y->setRange(-60, 360);
    this->chart->setAxisY(axis_y, series);
    this->chart->addSeries(this->series);
    this->chart->setTitle(tr("Kąty rakiety"));
    this->chart->setTheme(QChart::ChartThemeBrownSand);

    this->chart_view = new QChartView(this->chart);
    this->chart_view->setRenderHint(QPainter::Antialiasing);
    this->layout = new QVBoxLayout(ui->chart_frame);
    this->layout->addWidget(chart_view);
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

#define ACC_SENSITIVITY  0.00061
#define GYRO_SENSITIVITY 0.0175
#define ALPHA 0.6
#define DT 0.2

void MainWindow::read_data()
{
    while (this->port->canReadLine()) {
            QString line = this->port->readLine();
            //std::string temp;

            if (data.parseData(line) == 0) {
                ui->textEdit->append(line);

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

                ui->label_x_axis->setText(" " + QString(this->angX >= 0, ' ') + QString::number(this->angX, 'd', 2) + " °"); //QString::arg(double a, int fieldWidth = 0, char format = 'g', int precision = -1, QChar fillChar = QLatin1Char(' '))
                ui->label_y_axis->setText(" " + QString((this->angY - 90.0f) >= 0, ' ') + QString::number(this->angY - 90.0f, 'd', 2) + " °");
                ui->label_z_axis->setText(" " + QString(this->angZ >= 0, ' ') + QString::number(this->angZ, 'd', 2) + " °");

                ui->label_gyro_x->setText(" " + QString(gyroX >= 0, ' ') + QString::number(gyroX, 'd', 2) + " rad/s");
                ui->label_gyro_y->setText(" " + QString(gyroY >= 0, ' ') + QString::number(gyroY, 'd', 2) + " rad/s");
                ui->label_gyro_z->setText(" " + QString(gyroZ >= 0, ' ') + QString::number(gyroZ, 'd', 2) + " rad/s");

                ui->label_acc_x->setText(" " + QString(accX >= 0, ' ') + QString::number(accX, 'd', 2) + " m/s^2");
                ui->label_acc_y->setText(" " + QString(accY >= 0, ' ') + QString::number(accY, 'd', 2) + " m/s^2");
                ui->label_acc_z->setText(" " + QString(accZ >= 0, ' ') + QString::number(accZ, 'd', 2) + " m/s^2");

                qDebug() << this->angX << this->angY << this->angZ;

                this->fin2->setRotation(this->angX - 180.0);
                this->fin1->setRotation(-this->angX  - 180.0);

                this->fin3->setRotation(this->angY - 180.0);
                this->fin4->setRotation(-this->angY  - 180.0);

                ui->openGLWidget->setAngles(this->angX, this->angY - 90.0f, this->angZ);
                add_to_chart(this->angX);
                update();
            }
    }
}

void MainWindow::add_to_chart(const float &data) {
    if(this->series->count() == 200) {
        this->series->remove(counter - 200);
        this->series->append(this->counter, data);
        axis_x = new QValueAxis;
        axis_x->setRange(counter - 200, counter);
        this->chart->setAxisX(axis_x, series);
        this->counter += 1.0f;
        update();
    }
    else {
        this->series->append(this->counter, data);
        axis_x = new QValueAxis;
        axis_x->setRange(0, counter);
        this->chart->setAxisX(axis_x, series);
        this->counter += 1.0f;
        update();
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    // Output debug message and status message
    qDebug() << tr("Trwa szukanie urządzeń...");
    ui->textEdit->append(tr("Trwa szukanie urządzeń..."));

    // Get a list of available serial port devices
    QList<QSerialPortInfo> devices;
    devices = QSerialPortInfo::availablePorts();

    // Set the background color of the combo box based on whether devices were found
    if (devices.count() != 0) {
        ui->comboBox->setStyleSheet("color: rgb(0, 0, 0); background: rgb(255, 213, 1); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    }
    else {
        ui->comboBox->setStyleSheet("color: rgb(0, 0, 0); background: rgb(168, 13, 16); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
        qDebug() << tr("Żadne urządzenie nie zostało wykryte");
        ui->textEdit->append(tr("Żadne urządzenie nie zostało wykryte"));
    }

    // Clear the combo box and populate it with the names of the available devices
    ui->comboBox->clear();
    ui->comboBox->clear();
    for(int i = 0; i < devices.count(); i++) {
      QString str = devices.at(i).portName();
      qDebug() << str;
      ui->comboBox->addItem(str);
      ui->textEdit->append(tr("Znaleziono: ") + str);
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
        ui->textEdit->append(tr("Nie można połączyć - brak wykrytych urządzeń!"));
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
      ui->textEdit->append(tr("Otwarcie portu szeregowego się udało!"));
      ui->comboBox->setStyleSheet("color: rgb(0, 0, 0); background: rgb(34, 139, 34); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");

    } else {
      ui->textEdit->append(tr("Otwarcie portu szeregowego się nie udało!"));
    }
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(port->isOpen()) {
        this->port->close();
        ui->textEdit->append(tr("Zamknięto port!"));
        ui->comboBox->clear();
        ui->comboBox->setStyleSheet("color: rgb(0, 0, 0); background: rgb(168, 13, 16); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    }
    else {
        ui->textEdit->append(tr("Port nie jest otwarty!"));
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


void MainWindow::on_pushButton_6_clicked()
{
    this->fin1->setRotation(this->fin1->rotation() + 10);
    add_to_chart(counter * 2.0f);
}


void MainWindow::on_pushButton_6_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}


void MainWindow::on_pushButton_6_released()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}


void MainWindow::on_pushButton_7_pressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}


void MainWindow::on_pushButton_7_released()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
}



void MainWindow::on_pushButton_8_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    QPushButton *another = qobject_cast<QPushButton *>(ui->pushButton_9);
    another->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    QTranslator *translator = new QTranslator;
    if(!translator->load("/home/hubert/wds/wds-app/wds-app_pl_PL.qm")) {
        qDebug() << "Error in loading translation file";
    }
    QApplication::instance()->installTranslator(translator);
    ui->retranslateUi(this);
}


void MainWindow::on_pushButton_9_clicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    button->setStyleSheet("color: rgb(0, 0, 0); font-weight: bold; background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    QPushButton *another = qobject_cast<QPushButton *>(ui->pushButton_8);
    another->setStyleSheet("color: rgb(0, 0, 0); background: rgb(204, 199, 172); border: 2px solid rgb(0, 0, 0); border-radius: 7px;");
    QTranslator *translator = new QTranslator;
    if(!translator->load("/home/hubert/wds/wds-app/wds-app_en_EN.qm")) {
        qDebug() << "Error in loading translation file";
    }
    QApplication::instance()->installTranslator(translator);
    ui->retranslateUi(this);
}

