#include "mazegen.h"

#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mazegen w;
    w.show();
    return a.exec();
}
