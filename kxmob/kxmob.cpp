#include "kxmob.h"
#include <QFont>
#include <QApplication>
#include <QTextCodec>

void KxMob::init()
{
    QFont f("SimSun");
    f.setPixelSize(12);
    QApplication::setFont(f);
    //XMLNode::setGlobalOptions(XMLNode::char_encoding_GB2312);
    qputenv("QT_ANCHORLAYOUT_NO_SIMPLIFICATION", "1");
}

void KxMob::destroy()
{

}
