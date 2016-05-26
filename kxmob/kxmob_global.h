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
#include <QGraphicsWidget>
#include <QGraphicsView>
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


#ifdef KXFW_LIB
# define KXFW_API Q_DECL_EXPORT
#else
# define KXFW_API Q_DECL_IMPORT
#endif

/* private */
#include "kdatadef.h"

inline void qDeleteLater(QObject *obj)
{
    QMetaObject::invokeMethod(obj, "deleteLater", Qt::QueuedConnection);
}

#endif
