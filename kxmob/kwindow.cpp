﻿#include "stable.h"
#include "kwindow.h"
#include "kspacer.h"
#include "kxmlui.h"

#include "ktheme.h"

#include "kwindow_p.h"

KX_WINDOW_CREATOR_GLOBAL_STATIC(KWindow);


KWindowPrivate::KWindowPrivate()
{
	//这函数为FLALS时的作用，会导致IE的AxWidget在调用setParent时，触发所有Child均为NativeWindow.
	QApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
	m_bStopMyCloseExecution = false;
}

KWindowPrivate::~KWindowPrivate()
{

}


void KWindowPrivate::init()
{
	Q_Q(KWindow);

	m_isClosing = false;
	q->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	q->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	q->setRealWindow(false);
	QString style = q->styleSheet();
	q->setStyleSheet( "QGraphicsView { border-style: none}" );
	scene = new QGraphicsScene(q);
	q->setScene(scene);
	root = new KSpacer(NULL);
	root->setLayoutType(KWidget::VBox);
	root->setDragPolicy(KWidget::WindowMove);
	root->setFlag(QGraphicsItem::ItemClipsChildrenToShape);
	root->setParent(scene);
	scene->addItem(root);
	bool bOk = QObject::connect(&m_timerUpdate, SIGNAL(timeout()), q, SLOT(on_viewport_update_bugfix()));
	q->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
}


void KWindowPrivate::setFont( const QFont& f )
{
	if(scene == NULL)
		return;
	scene->setFont(f);
}

KWindow::KWindow( QWidget *parent /*= NULL*/ ) 
: QGraphicsView(parent)
, d_ptr(new KWindowPrivate)

{
	d_ptr->q_ptr = this;
	d_ptr->init();
	if(parent)
	{
		const QFont& f = parent->font();
		d_ptr->setFont(f);
	}
}

KWindow::KWindow( KWindowPrivate &dd, QWidget *parent /* = NULL*/ )
: QGraphicsView(parent) 
, d_ptr(&dd)
{
	d_ptr->q_ptr = this;
	d_ptr->init();
	if(parent)
	{
		const QFont& f = parent->font();
		d_ptr->setFont(f);
	}
}

KWindow::~KWindow()
{
	QApplication::removePostedEvents(this);
	delete d_ptr;
	d_ptr = NULL;
}

bool KWindow::event(QEvent * e)
{
//	if(e->type() == KThemeChangeEvent::EventType)
//	{
//		themeChange((KThemeChangeEvent*)e);
//		return true;
//	}
//	else if(e->type() == QEvent::Move)
//	{
//		emit posChanged();
//		return true;
//	}
    return QGraphicsView::event(e);
}

void KWindow::closeEvent( QCloseEvent *event )
{
	Q_D(KWindow);
	d->m_bCancelClose = false;
	emit aboutToClose();
	if(d->m_bCancelClose)
	{
		event->ignore();
	}
}

void KWindow::resizeEvent( QResizeEvent *event )
{
	setContentsRect();
	emit resized();
}

KWidget * KWindow::rootWidget()
{
	return d_func()->root;
}

QMargins KWindow::sceneMargins() const
{
	return d_func()->sceneMargin;
}

void KWindow::setSceneMargins( const QMargins& m )
{
	d_func()->sceneMargin = m;
	setContentsRect();
}

void KWindow::setContentsRect()
{
	Q_D(KWindow);

	QRect rt = rect();
	setSceneRect(rt);
	rt.adjust(d->sceneMargin.left(), d->sceneMargin.top(), -d->sceneMargin.right(), -d->sceneMargin.bottom());
	d->root->setGeometry(rt);
	d->root->setFixSize(rt.size());
}

void KWindow::construct()
{
	doThemeChange();
}

void KWindow::setRealWindow( bool on )
{
	/*
	当使用Qt::Window时，一定是创建窗口的。且是弹出式窗口，
	如果要使它是子窗口且是真窗口，则只有使用NativeWindow和Widget组合才行。
	*/
	/*
	只要具有Window属性，就一定是弹出窗口,它不能与WA_NativeWindow一起使用。在Qt中的概念widget为子窗口，Window为弹出窗口。
	而NativeWindow是强调Widget窗口为子窗口，且NativeWindow会导致该窗口很容易就重复的创建。
	*/
	setAttribute(Qt::WA_NativeWindow, on);
	Qt::WindowFlags flags = windowFlags();
	flags &= ~Qt::Window;
	flags |= Qt::Widget;
	setWindowFlags(flags);
}

void KWindow::abortCloseWindow()
{
	d_func()->m_bCancelClose = true;
}

void KWindow::showEvent( QShowEvent *event )
{
	Q_D(KWindow);
    QGraphicsView::showEvent(event);
	d->m_timerUpdate.start(512);
	emit visibleChanged();
}

void KWindow::hideEvent( QHideEvent *event )
{
	Q_D(KWindow);
    QGraphicsView::hideEvent(event);
	d->m_timerUpdate.stop();
	emit visibleChanged();
}

void KWindow::themeChange( KThemeChangeEvent *event )
{
	doThemeChange();
}

void KWindow::doThemeChange()
{
	Q_D(KWindow);

	foreach (QGraphicsItem* item, items())
	{
		KWidget* widget = qobject_cast<KWidget*>( item->toGraphicsObject() );
		if ( widget )
		{
			widget->doThemeChange();
		}
	}
	update();
}

void KWindow::skipMyCloseExecution()
{
	Q_D(KWindow);

	d->m_bStopMyCloseExecution = true;
}

void KWindow::close()
{
	Q_D(KWindow);

	if(d->m_bStopMyCloseExecution)
	{
        QGraphicsView::close();
		return;
	}

	if(d->m_isClosing)
		return;//自已加一层保护以防止m_bCancelClose被复盖。
	d->m_isClosing = true;
	d->m_bCancelClose = false;
	bool bAutoDelete = testAttribute(Qt::WA_DeleteOnClose);
	if(bAutoDelete)
	{
		setAttribute(Qt::WA_DeleteOnClose, false);
	}
    QGraphicsView::close();
	if(bAutoDelete)
	{
		if(!d->m_bCancelClose)
		{
			QMetaObject::invokeMethod(this, "deleteLater", Qt::QueuedConnection);
		}
		else
		{
			setAttribute(Qt::WA_DeleteOnClose, true);
		}
	}
	d->m_isClosing = false;
}

/*
由于win7的AeroSnap特性影响，可能会导致Qt内部的最大化最小化窗口失常。
*/
void KWindow::showNormal()
{
    QGraphicsView::showNormal();
}

void KWindow::showMaximized()
{
    QGraphicsView::showMaximized();
}

void KWindow::showMinimized()
{
    QGraphicsView::showMinimized();
}

void KWindow::showMaximizeOrRestore()
{
//	if(::IsMaximized(winId()))
//	{
//		::ShowWindow(winId(), SW_RESTORE);
//	}
//	else
//	{
//		//showMaximized();
//		::ShowWindow(winId(), SW_MAXIMIZE);
//	}
}

void KWindow::setFontSize( int fs )
{
	Q_D(KWindow);
	QFont &f = const_cast<QFont&>(font());
	f.setPixelSize(fs);
	setFont(f);
	d->setFont(f);
}

int KWindow::fontSize() const
{
	QFont &f = const_cast<QFont&>(font());
	return f.pixelSize();
}

QString KWindow::fontName() const
{
	QFont &f = const_cast<QFont&>(font());
	return f.family();
}

void KWindow::setFontName( const QString& name )
{
	Q_D(KWindow);
	QFont &f = const_cast<QFont&>(font());
	f.setFamily(name);
	setFont(f);
	d->setFont(f);
}

void KWindow::setBold( bool enable )
{
	Q_D(KWindow);
	QFont &f = const_cast<QFont&>(font());
	f.setBold(enable);
	setFont(f);
	d->setFont(f);
}

bool KWindow::bold() const
{
	QFont &f = const_cast<QFont&>(font());
	return f.bold();
}

void KWindow::setFont( const QFont& f )
{
	Q_D(KWindow);
    QGraphicsView::setFont(f);
	d->setFont(f);
}

void KWindow::on_viewport_update_bugfix()
{
	QApplication::postEvent(this, new QEvent(QEvent::UpdateRequest), Qt::LowEventPriority);
}

QSizeF KWindow::calcWindowPreferSize()
{
	Q_D(KWindow);
	KWidget *root = KWindow::rootWidget();
	root->setSizeToChild(true);
	root->invalidateLayout();
	QSizeF rs = root->minimumSize();
	QMargins m = d_func()->sceneMargin;
	return QSizeF(rs.width() + m.left() + m.right(), rs.height() + m.top() + m.bottom());
}

QString KWindow::skinName() const
{
	return QString();
}

void KWindow::setSkinName( const QString& name )
{
//	KTheme::setSkinName(this, name);
}


void KWindow::setAutoDeleteWhenAppQuit( bool on )
{
	if(on)
	{
		QApplication::connect(QApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(on_aboutToQuit()));
	}
	else
	{
		QApplication::disconnect(QApplication::instance(), SIGNAL(aboutToQuit()), this, SLOT(on_aboutToQuit()));
	}
}

void KWindow::on_aboutToQuit()
{
	delete this;
}
