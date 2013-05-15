// Created By July IGHOR. Please do not remove this line :)

#include <QtGui/QApplication>
#include "dropboxplugin.h"
#include <QTextCodec>
#include "qtsingleapplication.h"
#include "pluginengine.h"
#include "updateview.h"
#include "windows.h"

int main(int argc, char *argv[])
{
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());

	QStringList paramsList;
	for(int n=1;n<argc;n++)paramsList<<argv[n];

	if(paramsList.count()==0||paramsList.count()==1&&paramsList.first().toLower()=="/move")
	{
		QtSingleApplication confApp("ConfigWindow", argc, argv);
		DropboxPlugin settingsWindow;
		confApp.setActivationWindow(&settingsWindow);
		settingsWindow.show();
		return confApp.exec();
	}

	if(argc>1&&paramsList.first()=="/update")
	{
		QApplication aUpdate(argc, argv);
		UpdateView updateView(0);
		return aUpdate.exec();
	}
	QtSingleApplication a("PluginEngine", argc, argv);

	if(GetAsyncKeyState(VK_SHIFT)&&!paramsList.contains("/move",Qt::CaseInsensitive))
		paramsList<<"/move";

	QString messToSend="";
		if(paramsList.size()>0){messToSend=paramsList.join("::");}
	if(a.sendMessage(messToSend))
		return 0;

	PluginEngine engine(paramsList);
    QObject::connect(&a, SIGNAL(messageReceived(const QString&)),&engine, SLOT(append(const QString&)));
	
	if(engine.showSettings)
	{
		QProcess proc;
		proc.startDetached(a.applicationFilePath());
		proc.waitForStarted();
		return 0;
	}
return a.exec();
}





