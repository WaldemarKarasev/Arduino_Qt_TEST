#include "dialog.h"
#include "ui_dialog.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    arduino = new QSerialPort();

//    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
//    for (const QSerialPortInfo &serialPortInfo : QSerialPortInfo::availablePorts()) {
//        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
//        if(serialPortInfo.hasVendorIdentifier())
//        {
//            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
//        }
//        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
//        if(serialPortInfo.hasProductIdentifier())
//        {
//            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
//        }
//    }

    for(const QSerialPortInfo &serialPortInfo : QSerialPortInfo::availablePorts())
    {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
            if (serialPortInfo.vendorIdentifier() == arduino_vendor_ID) {
                if (serialPortInfo.productIdentifier() == arduino_product_ID) {
                    arduino_port_name = serialPortInfo.portName();
                    arduino_is_available = true;

                }
            }
        }
    }

    if (arduino_is_available)
    {
        arduino->setPortName(arduino_port_name);
        arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));

    }
    else
    {
        QMessageBox::warning(this, "Port error", "Couldn't find the Arduino");
    }

}

Dialog::~Dialog()
{
    if (arduino->isOpen()) {
        arduino->close();
    }
    delete ui;
}

void Dialog::on_pushButton_1_clicked()
{
    QString str = ui->state_label_1->text();
    qDebug() << str;
    int state = str.toInt();
    qDebug() << state;
    ui->state_label_1->setText(QString("%1").arg(!state));
    updateLED(QString("f%1").arg(!state));
}

void Dialog::on_pushButton_2_clicked()
{
    QString str = ui->state_label_2->text();
    int state = str.toInt();
    ui->state_label_2->setText(QString("%1").arg(!state));
    updateLED(QString("s%1").arg(!state));
}

void Dialog::on_pushButton_3_clicked()
{
    QString str = ui->state_label_3->text();
    int state = str.toInt();
    ui->state_label_3->setText(QString("%1").arg(!state));
    updateLED(QString("t%1").arg(!state));
}

void Dialog::updateLED(QString command)
{
    if (arduino->isWritable()) {
        arduino->write(command.toStdString().c_str());
    }
    else
    {
        qDebug() << "Couldn't write to serial!";
    }
}

void Dialog::readSerial()
{
    serialData = arduino->readAll();
    serialBuffer += QString::fromStdString(serialData.toStdString());
    qDebug() << serialBuffer;

    QStringList bufferSplit = serialBuffer.split(",");
    if (bufferSplit.length() < 3)
    {
        serialData = arduino->readAll();
        serialBuffer += QString::fromStdString(serialData.toStdString());
    }
    else
    {
        //bufferSplit[1] = good value
        qDebug() << bufferSplit;
        updateLCD(bufferSplit[1]);
        serialBuffer =  "";
    }

}

void Dialog::updateLCD(QString potentiometer_reading)
{
    ui->voltage_val_LDC_Number->display(potentiometer_reading);
}










