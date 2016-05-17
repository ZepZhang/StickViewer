#include "mainwindow.h"
#include <QApplication>
#include "serialportreader.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //SerialPortReader是自己写的一个类，里边实现了读取串口数据的功能
    //这里创建了这个类的一个对象，取名叫myReader
    //注意这个类的构造函数需要传一个参数，这个参数就是串口对象
    SerialPortReader myReader(&w.mySerialPort);
    //这里的意思是每有串口数据，myReader都会发送一个信号，告诉界面该刷新了
    QObject::connect(&myReader,SIGNAL(mySignal(QByteArray)), &w, SLOT(refreshUi(QByteArray)));
    w.setWindowTitle("Sticker Viewer ver0.1");
    w.setFixedSize(646, 454);
    w.show();
    return a.exec();
}
