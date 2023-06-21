#include "PiQtSocket.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PiQtSocket w;
    w.show();
    return a.exec();
}
