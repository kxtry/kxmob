#include "widget.h"
#include <QApplication>
#include "kxmob.h"
#include "kxmlui.h"
#include "kwidget.h"
#include "kwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    Q_INIT_RESOURCE(uishower);

    KxMob::init();

    KWindow *window = KXmlUI::windowFromFile(":/uishower.xml");
    window->show();

    return a.exec();
}
