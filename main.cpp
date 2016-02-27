#include "titanium.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    titanium w;
    w.show();

    return a.exec();
}
