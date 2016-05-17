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
    QSerialPort mySerialPort;

public slots:
    void refreshUi(QByteArray);

private slots:
    void on_openMyComBtn_clicked();

    void on_closeMyComBtn_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    //
    void refreshRadioButtons(QByteArray ba);
    void refreshTextEditors(QByteArray ba);
    void refreshCoordinates(QByteArray ba);
};

#endif // MAINWINDOW_H
