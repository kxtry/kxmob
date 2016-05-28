#ifndef _KXMOB_GLOBAL_H_
#define _KXMOB_GLOBAL_H_

/* Qt library */
#include <QtGlobal>
#include <QtCore>
#include <QObject>

#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QMargins>
#include <QPointer>
#include <QColor>
#include <QIcon>
#include <QLatin1String>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QPair>
#include <QVariant>
#include <QPixmap>
#include <QEvent>
#include <QFontMetrics>
#include <QFontMetricsF>
#include <QGraphicsLinearLayout>
#include <QGraphicsAnchorLayout>
#include <QGraphicsColorizeEffect>
#include <QLineEdit>
#include <QGraphicsProxyWidget>
#include <QTextFormat>
#include <QTextOption>
#include <QTextCursor>
#include <QFontDatabase>
#include <QFrame>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <QDebug>
#include <QMetaEnum>

#include <QGraphicsWidget>
#include <QGraphicsView>
#include <QCoreApplication>
#include <QApplication>


inline void qDeleteLater(QObject *obj)
{
    QMetaObject::invokeMethod(obj, "deleteLater", Qt::QueuedConnection);
}

#endif
