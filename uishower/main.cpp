#include "widget.h"
#include <QApplication>
#include "kxmob.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    KxMob::init();

    return a.exec();
}
