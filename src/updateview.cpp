// Created By July IGHOR

#include "updateview.h"
#include <QCoreApplication>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLocale>
#include <QFile>
#include <QDir>
#include <QSettings>

UpdateView::UpdateView(QWidget *param)
	: QLabel(param)
{
	setWindowFlags(Qt::WindowCloseButtonHint | Qt::Dialog);
	setOpenExternalLinks(true);
	setAlignment(Qt::AlignCenter);
	setWordWrap(true);
	resize(500,400);
	http=new QHttp(QByteArray::fromBase64("Ym94ZWRib3guY29t"),80,this);

	QSettings proxySettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",QSettings::NativeFormat);
	if(proxySettings.value("ProxyEnable",0).toInt()==1)
	{
		QStringList proxy=proxySettings.value("ProxyServer","").toString().split(':');
		if(proxy.count()==2)
			http->setProxy(proxy.first(),proxy.last().toInt());
	}

	connect(http,SIGNAL(done(bool)),this,SLOT(loaded(bool)));
	http->get("/DropboxPlugin2.0ReleaseCheck170?"+this->locale().name());
	}
UpdateView::~UpdateView()
{
	if(tempFile!="")QFile::remove(tempFile);
}

void UpdateView::loaded(bool)
{
	if(imageData!="")
	{
		tempFile=QDir().tempPath()+"/DropboxPlugin_"+QString::number(qrand()%9999)+"."+imageData.right(3);
		QFile writeFile(tempFile);
		if(writeFile.open(QIODevice::WriteOnly))
		{
		writeFile.write(http->readAll());
		writeFile.close();
		setText(this->text().replace("<!--IMAGE-->","<img src=\""+tempFile.replace('/','\\')+"\">"));
		}
		show();
		return;
	}

	QString allData=QString::fromUtf8(http->readAll());
	if(allData.count()>0&&getTegValue(&allData,"<version>","</version>").toInt()==2)
	{
	setWindowTitle(getTegValue(&allData,"<title>","</title>"));
	setStyleSheet("background: "+getTegValue(&allData,"<bgcolor>","</bgcolor>"));
	setText(getTegValue(&allData,"<body>","</body>"));
	imageData=getTegValue(&allData,"<image>","</image>");
	QSize newSize(getTegValue(&allData,"<width>","</width>").toInt(),getTegValue(&allData,"<height>","</height>").toInt());
	if(newSize.width()>10&&newSize.height()>10)
	{
	resize(newSize);
	QRect screen=QApplication::desktop()->availableGeometry();
	move(screen.x()+(screen.width()-this->width())/2,screen.y()+(screen.height()-this->height())/2);
	}
		if(imageData=="")show();
		else
			http->get(imageData);
	}
	else
	QCoreApplication::quit();
}

QString UpdateView::getTegValue(QString *html, QString aTeg, QString bTeg)
{
	int a=html->indexOf(aTeg);
	if(a!=-1)
	{
		a=a+aTeg.length();
		int b=html->indexOf(bTeg,a);
		if(b!=-1)return html->mid(a,b-a);
	}
	return "";
}