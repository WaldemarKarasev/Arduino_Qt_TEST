#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.setFixedSize(800, 258);
    w.setWindowTitle("Serial Port Terminal");
    w.show();
    return a.exec();
}
