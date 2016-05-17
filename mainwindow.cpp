#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->openMyComBtn->setEnabled(true);
    ui->closeMyComBtn->setEnabled(false);
    //this button is just for debugging
    ui->pushButton->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
//点击打开串口时，对mySerialPort对象的一些属性进行设置，然后用open打开串口
void MainWindow::on_openMyComBtn_clicked()
{
    mySerialPort.setPortName(ui->portNameComboBox->currentText());
    mySerialPort.setBaudRate(QSerialPort::Baud115200);

    if (!mySerialPort.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(NULL, "warning", "can't open serialport!!! ", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    ui->openMyComBtn->setEnabled(false);
    ui->closeMyComBtn->setEnabled(true);
}
//同理当点击关闭串口函数时，进行一些处理
void MainWindow::on_closeMyComBtn_clicked()
{
    mySerialPort.close();
    ui->openMyComBtn->setEnabled(true);
    ui->closeMyComBtn->setEnabled(false);
}
//这是一个槽函数，理解
void MainWindow::refreshUi(QByteArray content)
{
    refreshTextEditors(content);
    refreshCoordinates(content);
}

void MainWindow::refreshTextEditors(QByteArray ba)
{
    QVariant x,y;
    x = int((unsigned char)(ba[0]));
    y = int((unsigned char)(ba[1]));
    ui->lineEdit->setText(x.toString());
    ui->lineEdit_2->setText(y.toString());
}
//这里需理解QcustomPlot是我采用的一个开源模块，用于绘制坐标系
void MainWindow::refreshCoordinates(QByteArray ba)
{
    QCustomPlot *customPlot = ui->customPlot;
    customPlot->addGraph();
    customPlot->graph(0)->addData(double((unsigned char)(ba[0])), double((unsigned char)(ba[1])));
    customPlot->xAxis->setRange(0, 260);
    customPlot->yAxis->setRange(0, 260 );
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::red, 10));
    customPlot->replot();
    customPlot->clearGraphs();
}

//just for debugging
void MainWindow::on_pushButton_clicked()
{
    /*
    QCustomPlot *customPlot = ui->customPlot;
    // generate some data:
    QVector<double> x(101), y(101); // initialize with entries 0..100
    for (int i=0; i<101; ++i)
    {
      x[i] = i/50.0 - 1; // x goes from -1 to 1
      y[i] = x[i]*x[i]; // let's plot a quadratic function
    }
    // create graph and assign data to it:
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();
    */
    QByteArray ba;
    ba.resize(2);
    ba[0]= 0xff;
    ba[1] = 0x12;
    refreshTextEditors(ba);
    refreshCoordinates(ba);
}
