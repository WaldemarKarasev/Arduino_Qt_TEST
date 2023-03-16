#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void updateLED(QString command);
    void readSerial();
    void updateLCD(QString potentiometer_reading);


private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;
    static const quint16 arduino_vendor_ID = 9025;
    static const quint16 arduino_product_ID = 67;
    QString arduino_port_name = "";
    bool arduino_is_available = false;
    QByteArray serialData;
    QString serialBuffer = "";
};
#endif // DIALOG_H
