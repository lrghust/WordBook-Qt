#include "load.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Load w;
    w.show();

    return a.exec();
}
