#include <QCoreApplication>
#include <QtSerialPort/QSerialPort>
#include <QDebug>
//https://www.qtcentre.org/threads/58536-Using-QtSerialPort-in-a-console-application
QSerialPort serial;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

  //  serial.setPortName("/dev/ttyUSB0");
    serial.setPortName("/dev/ttyACM0");

    serial.open(QIODevice::ReadWrite);
  //  serial.setBaudRate(QSerialPort::Baud115200);
        serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    serial.write("-helloworld-");
    //serial.close();

    while (1)
    {
        if (serial.bytesAvailable()>0||serial.waitForReadyRead(10))
        {
            QByteArray ba;
            ba=serial.readAll();
            serial.write(ba);
            qDebug()<<ba;
        }
    }
    serial.close();
    return a.exec();
}
