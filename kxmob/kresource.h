#ifndef _KRESOURCE_H_
#define _KRESOURCE_H_

#include "kxapi.h"

class QPixmap;
class QDomDocument;

class KXFW_API KResource
{
public:
	static QImage loadImage(const QString& path);
	static QPixmap loadPixmap(const QString& path, bool bTheme, bool bCache);
	static QString pixmapCacheKey(const QString& path, bool bRaw);
    static QByteArray loadRawData(const QString& path);
    static bool loadXml(const QString& path, QDomDocument& xml);
	static QString absoluteFileName(const QString& path);

	//addSearchPath("qrcxml", "D:\\xueren\\kkwork\\kk\\trunk\\kk");
	//addSearchPath("qrcxml", "c:\\test");
	//qrcxml:/mypath/a.png等价于c:\\test/mypath/a.png
	static void addSearchPath(const QString &prefix, const QString &path);
	static QStringList searchPaths(const QString & prefix);

	/*appdata = %appdata%*/
	/*appdir = exe's dir*/
	static void addDefaultSearchPath();
};

#endif
