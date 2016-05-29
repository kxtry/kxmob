﻿#ifndef _KXMLUI_H_
#define _KXMLUI_H_

#include "kxapi.h"

class QGraphicsItem;
class KWidget;
class QGraphicsView;
class KWindow;
class KHelper;
class QWidget;
struct QDomElement;

class KWidgetCreatorBase;
class KWindowCreatorBase;
class KHelperCreatorBase;

#define KX_HELPER_CREATOR_GLOBAL_STATIC(helper) \
	static const KCreator<helper,KHelper,QObject,KHelperCreatorBase> kx_helper_creator_global_static_##helper(#helper);
#define KX_WIDGET_CREATOR_GLOBAL_STATIC(widget) \
	static const KCreator<widget,KWidget,QGraphicsItem,KWidgetCreatorBase> kx_widget_creator_global_static_##widget(#widget);
#define KX_WINDOW_CREATOR_GLOBAL_STATIC(window) \
	static const KCreator<window,KWindow,QWidget,KWindowCreatorBase> kx_window_creator_global_static_##window(#window);

class KXFW_API KHelperCreatorBase
{
public:
    KHelperCreatorBase(const QString& objectClassName);
	virtual ~KHelperCreatorBase();
    QString className() const;
	virtual KHelper *create(QObject *parent) const = 0;
	virtual const QMetaObject *metaObject() const = 0;

private:
    QString m_className;
};

class KXFW_API KWidgetCreatorBase
{
public:
    KWidgetCreatorBase(const QString& widgetClassName);
    virtual ~KWidgetCreatorBase();
    QString className() const;
    virtual KWidget *create(QGraphicsItem *parent) const = 0;
    virtual const QMetaObject *metaObject() const = 0;

private:
    QString m_className;
};

class KXFW_API KWindowCreatorBase
{
public:
    KWindowCreatorBase(const QString& windowClassName);

	virtual ~KWindowCreatorBase();
    QString className() const;
	virtual KWindow *create(QWidget *parent) const = 0;
	virtual const QMetaObject *metaObject() const = 0;

private:
    QString m_className;
};

template<class T, class TBase, class TRoot, class TCreator>
class KCreator : public TCreator
{
public:
    KCreator(const QString& className) : TCreator(className)
	{
	}

	virtual ~KCreator()
	{
	}

	virtual TBase *create(TRoot *parent) const
	{
		return new T(parent);
	}

	virtual const QMetaObject *metaObject() const
	{
		return &T::staticMetaObject;
	}
};

class KMethodInvokerOrg
{
public:
	KMethodInvokerOrg();
	~KMethodInvokerOrg();
	/*增加一个对像，可供信号连接或激发函数的参数输入。*/
	void addObject(const QString& objName, QObject* obj);
	/*信号量连接*/
	void addReceiver(QObject* obj, const QString& sender, const QByteArray& signal, const QByteArray& slot, Qt::ConnectionType itype);
	/*方法：激发信号或激发Invoke函数或事件槽函数*/
	void addMethod(QObject *obj, const QByteArray& invoke, const QByteArray& argv, Qt::ConnectionType itype);
	void execute();
	void clearAll();
private:
	QHash<QString, QObject*> m_hashObjects;
	struct EventReceiver
	{
		QObject		*obj;
		QString		sender;
		QByteArray		signal;
		QByteArray		slot;
		Qt::ConnectionType	itype;
	};
	QList<EventReceiver> m_lstRecv;
	struct MethodInvoker
	{
		QObject					*obj;
		QByteArray				invoke;
		QByteArray				argv;
		Qt::ConnectionType		itype;
	};
	QList<MethodInvoker> m_lstMethod;
};



class KXmlUI
{
public:
    static KXFW_API bool initSkin(const QString& file);
	static KXFW_API bool initSkin(const QByteArray& memory);
	static KXFW_API bool widgetFromFile(const QString& file, KWidget *parent = NULL);
    static KXFW_API bool widgetFromMemory(const QByteArray& memory, KWidget *parent = NULL );
	static KXFW_API KWindow* windowFromFile(const QString& file, QWidget *parent = NULL);
	static KXFW_API KWindow* windowFromMemory(const QByteArray& memory, QWidget *parent = NULL);
    static KXFW_API bool setPropertyEx(QObject *obj, const QString& name, const QString& value);
    static KXFW_API bool setPropertyEx(QObject *obj, const QString& name, const QVariant& val);

public:
	static void setSkin(QObject *objItem, const QString& skin);
private:
	//构造出皮肤池。
	static QMetaObject *getMetaObject(const char* className);
    static bool createSkinPool(QDomElement& xml);
    static bool createUITreeFromXml(QDomElement& xml, KWidget *parent);
    static KWindow* createUITreeFromXml(QDomElement& xml, QWidget *parent);
    static void createElements(KWidget *item, QDomElement& node);
    static bool createChild(QDomElement& child, KWidget *parent);
    static void setProperties(QDomElement& child, QObject* item);
	static QVariant setProperty(QObject *objItem, const char* attrName, const char* attrValue);
    static KWindow *createWindow(const QString& className, QWidget *parent);
    static KWidget *createWidget(const QString& className, KWidget *parent);
    static bool setDefaultDataProperty(QObject *widget, QDomElement child);
	/*设置事件*/
    static void connectSlot(QObject *obj, QDomElement& node);
	/*激发函数*/
    static void invokeMethod(QObject *obj, QDomElement& node);
	/*设置数据*/
    static void setData(KWidget *obj, QDomElement& node);
    static bool buildTreeData(QList<QVariant>& list, QDomElement& node);

    //uihelper
    static bool executeUIHelperFromXml(QDomElement& xml, QObject *parent);
    static bool executeHelper(QDomElement& child, QObject *parent, QObject *root);
    static KHelper *createHelper(const QString& className, QObject *parent);

	/*skin*/
    static bool initSkin(QDomElement& root);
};

#endif
