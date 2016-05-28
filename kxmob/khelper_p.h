﻿#ifndef _KHELPER_P_H_
#define _KHELPER_P_H_

#include "kxapi.h"

class KHelper;

class KXFW_API KHelperPrivate
{
	Q_DECLARE_PUBLIC(KHelper)
public:
	QString targetPath;
	QPointer<QObject> objTarget;
	QPointer<QObject> objRoot;
public:
	KHelperPrivate();
	virtual ~KHelperPrivate();

	bool doExecute();
	QObject *viewObject();

protected:
	KHelper *q_ptr;
};

#endif
