#include "mainwindow.h"
#include <QApplication>
#include "serialportreader.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    SerialPortReader myReader(&w.mySerialPort);
    QObject::connect(&myReader,SIGNAL(mySignal(QByteArray)), &w, SLOT(refreshUi(QByteArray)));
    w.setWindowTitle("Sticker Viewer ver0.1");
    w.setFixedSize(646, 454);
    w.show();
    return a.exec();
}
