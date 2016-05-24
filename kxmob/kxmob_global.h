#ifndef KXMOB_GLOBAL_H
#define KXMOB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KXMOB_LIBRARY)
#  define KXMOBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KXMOBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KXMOB_GLOBAL_H
