#include "stdafx.h"
#include "kwindow.h"
#include "kspacer.h"
#include "kxmlui.h"
#include "kwindow_p.h"
#include "ktheme.h"

KX_WINDOW_CREATOR_GLOBAL_STATIC(KWindow);

KWindowPrivate::KWindowPrivate()
{
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
	QString style = q->styleSheet();
	q->setStyleSheet( "QGraphicsView { border-style: none}" );
	scene = new QGraphicsScene(q);
    q->setScene(scene);
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
	if(e->type() == KThemeChangeEvent::EventType)
	{
		themeChange((KThemeChangeEvent*)e);
		return true;
	}
	else if(e->type() == QEvent::Move)
	{
		emit posChanged();
		return true;
	}
	return __super::event(e);
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

void KWindow::abortCloseWindow()
{
	d_func()->m_bCancelClose = true;
}

void KWindow::showEvent( QShowEvent *event )
{
	Q_D(KWindow);
	__super::showEvent(event);
	emit visibleChanged();
}

void KWindow::hideEvent( QHideEvent *event )
{
	Q_D(KWindow);
	__super::hideEvent(event);
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
		__super::close();
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
	__super::close();
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
	//__super::showNormal();
	::ShowWindow(winId(), SW_NORMAL);
}

void KWindow::showMaximized()
{
	//__super::showMaximized();
	::ShowWindow(winId(), SW_MAXIMIZE);
}

void KWindow::showMinimized()
{
	//__super::showMinimized();
	::ShowWindow(winId(), SW_MINIMIZE);
}

void KWindow::showMaximizeOrRestore()
{
	if(::IsMaximized(winId()))
	{
		::ShowWindow(winId(), SW_RESTORE);
	}
	else
	{
		//showMaximized();
		::ShowWindow(winId(), SW_MAXIMIZE);
	}
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
	__super::setFont(f);
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
	KTheme::setSkinName(this, name);
}

bool KWindow::winEvent( MSG *pMsg, long *result )
{
	if(pMsg->message == WM_LBUTTONDOWN)
	{
		QGraphicsScene *gs = scene();
		while(gs && !gs->isActive())
		{
			/*
			中文输入法BUG-fixed.
			中文输入法共有两处BUG，此是一处，另一处是inputMethodEvent中的属性导致。
			当QEvent::WindowActivate被别的对象吃掉或QEvent::WindowDeactivate事件被处理多次，可能会导致activationRefCount为负数，这时会导致中文输入法输入故障。
			故发送一个Active消息进行解琐，目的使相应的计数器重置为0。
			*/
			QEvent winActivate(QEvent::WindowActivate);
			QApplication::sendEvent(gs, &winActivate);
		}
	}

	return false;
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
