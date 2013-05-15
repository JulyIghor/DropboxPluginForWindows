// Created By July IGHOR

#include "pluginengine.h"
#include <QUrl>
#include <QClipboard>
#include <QSettings>
#include <QFileInfo>
#include <QFile>
#include <QMessageBox>
#include <QLocale>
#include <QDateTime>
#include <QDir>
#include <QApplication>
#include "windows.h"
#include <QProcess>
#include <QDate>
#include <QTextCodec>
#include <QDesktopServices>

PluginEngine::PluginEngine(QStringList argum)
	: QObject()
{
	interval=2000;
	showSettings=false;
	arguments=argum;
	if(arguments.count()>0)
	{
	timeOut = new QTimer(this);
	connect(timeOut,SIGNAL(timeout()),this,SLOT(timeOutSlot()));
	QStringList uaLanguage;
	QStringList ruLanguage;
Language << "File with same name already exists"
		 << "Replace or Rename existing file ?"
		 << "Replace"
		 << "Rename"
		 << "Cancel";
uaLanguage << "Файл з таким іменем вже існує"
		   << "Замінити чи перейменувати файл ?"
		   <<"Замінити"
		   <<"Перейменувати"
		   <<"Скасувати";
ruLanguage << "Файл с таким именем уже существует"
		   << "Заменить или перейменовать файл ?"
		   <<"Заменить" 
		   <<"Перейменовать"
		   <<"Отменить";
		QLocale count;
		if(count.language()==QLocale::Ukrainian)Language=uaLanguage;
		if(count.language()==QLocale::Russian)Language=ruLanguage;

		settings=new QSettings("JulySoft©","Dropbox Plugin");
		myDropboxDir=getMyDropboxDir();
		myDropboxID=settings->value("MyDropboxID","").toString().replace("\\","/");
		subDir=settings->value("SubDir","").toString();
		if(!subDir.isEmpty())
		subDir.replace("\\","/").replace(":","").replace("*","").replace("?","").replace("\"","").replace("<","").replace(">","").replace("|","");
		if(!subDir.isEmpty()&&subDir.right(1)!="/")subDir.append("/");
		if(settings->value("OldUrlStyle",true).toBool())dropboxUrl="https://dl.dropbox.com/u/";
		else dropboxUrl="https://dl.dropboxusercontent.com/u/";
		if((myDropboxDir!="")&&(myDropboxID!=""))
		{
		filesList<<arguments.join("::");
		reStartTimer();
		}
	else showSettings=true;
	}
	else showSettings=true;
}

QString PluginEngine::getMyDropboxDir()
{
QSettings settings("JulySoft©","Dropbox Plugin");
	QByteArray result;
	QString dbPath=QSettings("HKEY_CURRENT_USER\\Software\\Dropbox",QSettings::NativeFormat).value("InstallPath").toString().replace("\\bin","");
	if(QFile::exists(dbPath+"\\host.dbx"))dbPath+="\\host.dbx";
	else dbPath+="\\host.db";
	QFile readDb(dbPath);
	if(readDb.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		result=QByteArray::fromBase64(readDb.readAll().split('\n').last()).replace('\\','/');
		readDb.close();
	}
	if(!QFile::exists(result+"\\Public"))
		result=settings.value("MyDropboxDir","").toString().replace("\\","/").toAscii();
	if(!QFile::exists(result+"\\Public"))
	{
		QStringList findDropboxPublic;
		findDropboxPublic<<QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation).replace('/','\\')+"\\Dropbox"<<QDesktopServices::storageLocation(QDesktopServices::HomeLocation).replace('/','\\')+"\\Dropbox"<<"C:\\Dropbox"<<"D:\\Dropbox"<<"E:\\Dropbox";
		for(int n=0;n<findDropboxPublic.count();n++)
		if(QFile::exists(findDropboxPublic.at(n)+"\\Public"))
		{
			result=findDropboxPublic.at(n).toAscii();
			break;
		}
	}
	result.replace('/','\\');
	return result;
}

void PluginEngine::timeOutSlot()
{
	for(int n=0;n<filesList.size();n++)
		workAtArgumentList(filesList.at(n).split("::"));
		
	clipBoardLinks.sort();
	QApplication::clipboard()->setText(clipBoardLinks.join("\n"));
	if(settings->value("isSoundEnabled",true).toBool())MessageBeep(MB_ICONWARNING);

	if(settings->value("canCheckUpdates",true).toBool()&&(settings->value("lastUpdateCheck",QDate()).toDate()!=QDate::currentDate()))
	{
		QProcess proc;
		proc.startDetached(QCoreApplication::applicationFilePath(),QStringList("/update"));
		proc.waitForStarted();
		settings->setValue("lastUpdateCheck",QDate::currentDate());
	}

	QCoreApplication::quit();
	if(showSettings)
	{
		QProcess proc;
		proc.startDetached(QApplication::applicationFilePath());
		proc.waitForStarted();
	}
}

void PluginEngine::reStartTimer()
{
	timeOut->stop();
	timeOut->start(interval);
}

void PluginEngine::append(const QString &str)
{
	if(str!="")
	{
		timeOut->stop();
		filesList<<str;
		reStartTimer();
	}
}

void PluginEngine::workAtArgumentList(QStringList list)
{
	bool move=list.contains("/move",Qt::CaseInsensitive);
	int minArgCount=1;
	if(move)minArgCount=2;
	if(list.count()<minArgCount){showSettings=true; return;}
	for(int i=0;i<list.count();i++)
	{
	QString sourceFile=list.at(i);sourceFile.replace("\\","/");
	if((sourceFile!="/move")&&(sourceFile!="")&&QFile::exists(sourceFile))
	{
	if(QFileInfo(sourceFile).isFile())
	{
	QString completeFileName=QFileInfo(sourceFile).fileName();
	QString dropboxPublic=myDropboxDir+"/Public/"+subDir;
	dropboxPublic.replace("\\","/");

	if(!QFile::exists(dropboxPublic))QDir().mkpath(dropboxPublic);
	QString destFile=dropboxPublic+completeFileName;
	if(sourceFile.left(dropboxPublic.length())!=dropboxPublic)
	{
	if(QFile::exists(destFile))
	{
		QMessageBox msgBox;
		msgBox.setWindowTitle("Dropbox Copy Plugin");
		msgBox.setText(Language.at(0)+"\n"+destFile.replace("/","\\"));
		msgBox.setInformativeText(Language.at(1));
		msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Save);
		msgBox.setIcon(QMessageBox::Question);
		msgBox.setButtonText(QMessageBox::Save,Language.at(2));
		msgBox.setButtonText(QMessageBox::Discard,Language.at(3));
		msgBox.setButtonText(QMessageBox::Cancel,Language.at(4));
		int ret = msgBox.exec();
		if(ret==QMessageBox::Cancel)move=false;
		if(ret==QMessageBox::Save)QFile::remove(destFile);
		if(ret==QMessageBox::Discard)
		{
			completeFileName=QFileInfo(destFile).completeBaseName()+QDateTime::currentDateTime().toString("_yyyy.MM.dd_HH.mm.ss.")+QFileInfo(destFile).suffix();
			destFile=dropboxPublic+completeFileName;
		}
	}
		if(destFile!=sourceFile)
		{
			QFile::copy(sourceFile,destFile);
			if(move&&QFile::exists(destFile))QFile::remove(sourceFile);
		}
	}
	clipBoardLinks << QString(QUrl(dropboxUrl+myDropboxID+"/"+subDir+completeFileName).toEncoded());
	}
	showSettings=false;
		}		
	}
}