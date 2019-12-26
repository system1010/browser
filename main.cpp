#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.resize(1200,740);
    w.move(165,0);
    w.show();
    return a.exec();
}
