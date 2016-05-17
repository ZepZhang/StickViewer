#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QMessageBox>
#include "serialportreader.h"
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //QSerialPort 这个类是Qt提供的，这个类完成了串口必备的功能，包括初始化，底层驱动硬件等等
    QSerialPort mySerialPort;

    //以下的几个槽根据名字可以理解，但要想一下，为什么有的是public有的是private
public slots:
    void refreshUi(QByteArray);

private slots:
    void on_openMyComBtn_clicked();

    void on_closeMyComBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //以下几个函数根据名字可以理解
    void refreshRadioButtons(QByteArray ba);
    void refreshTextEditors(QByteArray ba);
    void refreshCoordinates(QByteArray ba);
};

#endif // MAINWINDOW_H
