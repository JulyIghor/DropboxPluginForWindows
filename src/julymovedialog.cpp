// Created By July IGHOR

#include "julymovedialog.h"
#include <QProcess>
#include <QDesktopServices>
JulyMoveDialog::JulyMoveDialog(QWidget *parent)
	: QWidget(parent)
{
	wasDropboxStarted=false;
	dropBoxAppFile=QDesktopServices::storageLocation(QDesktopServices::ApplicationsLocation).replace("\\","/")+"/Dropbox/Dropbox.lnk";
	if(QFile::exists(dropBoxAppFile))
	{
		dropBoxAppFile=QFileInfo(dropBoxAppFile).symLinkTarget();
		if(!QFile::exists(dropBoxAppFile))dropBoxAppFile="";
	}	else	dropBoxAppFile="";

	ui.setupUi(this);
	setWindowModality(Qt::ApplicationModal);
	setWindowFlags(Qt::Tool);

	scanDir = new JulyScanDir(this);
	scanDir->setFilesFilter("*");
    scanDir->setSearchSubFolders(true);
    scanDir->setSearchHidden(true);
	connect(scanDir,SIGNAL(fileChanged(QString)),this,SLOT(fileChanged(QString)));
	connect(scanDir,SIGNAL(loadedList(QStringList)),this,SLOT(loadedList(QStringList)));
	connect(scanDir,SIGNAL(dirChanged(QString)),this,SLOT(dirChanged(QString)));
	connect(scanDir,SIGNAL(errorHeppend(int)),this,SLOT(errorHeppend(int)));
}

JulyMoveDialog::~JulyMoveDialog(){}

void JulyMoveDialog::moveFolder(QString t_oldFile,QString t_newFile)
{
		replaceState=0;
		lastOldDir=t_oldFile.replace("\\","/");
		lastNewDir=t_newFile.replace("\\","/");
		t_dirsList.clear();
		setGeometry(this->parentWidget()->geometry());
		setFixedSize(this->width(),this->height());
		ui.progressBar->setValue(0);
		ui.progressText->setText("");
		ui.statusText->setText(startingText);
		show();
        scanDir->setStartDir(t_oldFile);
		scanDir->scanDir();
}

void JulyMoveDialog::fileChanged(QString t_file)
{
	ui.progressText->setText(t_file.replace("/","\\"));
}

void JulyMoveDialog::dirChanged(QString t_dir)
{
	t_dirsList << t_dir;
}

void JulyMoveDialog::errorHeppend(int)
{
	loadedList(QStringList());
}

void JulyMoveDialog::loadedList(QStringList t_list)
{
	bool onceSkipped=false;
	int t_filesCount=t_list.size();
	ui.statusText->setText(processingMove);

	for(int t_n=0;t_n<t_dirsList.size();t_n++)
	QDir().mkpath(lastNewDir+t_dirsList.at(t_n).right(t_dirsList.at(t_n).length()-lastOldDir.length()));
bool t_errorHeppend=false;
	for(int t_n=0;t_n<t_filesCount;t_n++)
	{
		QString t_curFile=t_list.at(t_n);
		ui.progressText->setText(t_curFile.replace("/","\\"));
		ui.progressBar->setValue((double)t_n/(double)t_filesCount*100);
		ui.progressBar->repaint();
		QString t_newFile=lastNewDir.replace("/","\\")+t_curFile.right(t_curFile.length()-lastOldDir.length());

bool t_replace=true;
 if(QFile::exists(t_newFile))
		{
if(replaceState==0)
{
		QMessageBox msgBox;
 msgBox.setIcon(QMessageBox::Question);
 msgBox.setText(replaceAtempt.split("\n").at(0)+" \""+t_newFile.replace("/","\\")+"\"");
 msgBox.setInformativeText(replaceAtempt.split("\n").at(1));
 msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll | QMessageBox::Cancel);
 msgBox.setDefaultButton(QMessageBox::Yes);
 int ret = msgBox.exec();
 switch (ret) {
   case QMessageBox::Yes:
	   t_replace=true;
       break;
   case QMessageBox::YesToAll:
	   t_replace=true;
	   replaceState=1;
       break;
   case QMessageBox::No:
	   t_replace=false;
	   onceSkipped=true;
       break;
   case QMessageBox::NoToAll:
	   t_replace=false;
	   onceSkipped=true;
	   replaceState=-1;
	   break;
   case QMessageBox::Cancel:
	   t_errorHeppend=true;
	   t_n=t_filesCount;
	   break;
   default:
       break;
 }
}
 if(replaceState==1)t_replace=true;
 if(replaceState==-1)t_replace=false;
	if(t_replace)
		QFile::remove(t_newFile);
		}
	if(!QFile::exists(t_newFile))QFile::copy(t_curFile,t_newFile);
	if(!QFile::exists(t_newFile))
	{
		t_errorHeppend=true;
		t_n=t_filesCount;
	}
	else
	if(t_replace)QFile::remove(t_curFile);
	}
if(!t_errorHeppend)
{
	if(!onceSkipped)
	{
		QProcess proc;
		proc.start("cmd /c rd /s /q \""+lastOldDir.replace("/","\\")+"\"");
		proc.waitForFinished();
	}
}
	ui.progressBar->setValue(100);
	hide();
	if(!t_errorHeppend)
	{
		if(dropBoxAppFile=="")
		QMessageBox::information(this,this->windowTitle(),copyFinishedText);
		else
		{
		if(wasDropboxStarted)
		{
			QProcess proc;
			proc.startDetached(dropBoxAppFile.replace("/","\\"), QStringList("/home"));
			proc.waitForFinished();
		}
			QMessageBox::information(this,this->windowTitle(),copyFinishedText.split("\n").at(0));
		}
	}
	else
	QMessageBox::critical(this,this->windowTitle(),copyErrorText);
}

