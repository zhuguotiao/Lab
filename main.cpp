#include "masterviw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MasterViw w;
    w.show();
    return a.exec();
}
