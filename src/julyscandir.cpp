// JulySoft ScanDir Threaded Class v1.25
// Created By JULY IGHOR. Please do not edit this line :)

#include "julyscandir.h"

JulyScanDir::JulyScanDir(QObject *parent)
	: QThread(parent)
{
	j_canSearchSubFoldersFirst=true;
	j_currentFileNum=0;
	j_canSearchSubFolders=true;
	j_isRegExpEnabled=false;
	j_isSearchingHidden=false;
	j_filesFilter=QStringList("*");
}

JulyScanDir::~JulyScanDir()
{
	stopSearching();
}

// Prepare Functions
void JulyScanDir::setSubFoldersFirst(bool t_on)
{
	j_canSearchSubFoldersFirst=t_on;
}

void JulyScanDir::setStartDir(QString dirName)
{
	setStartDirs(dirName.split(";;"));
}

void JulyScanDir::setStartDirs(QStringList dirsNames)
{
	if(!isRunning())
	{
	j_startDirsPath.clear();
		for(int t_n=0;t_n<dirsNames.size();t_n++)
		{
		QString t_currentDirPath=dirsNames.at(t_n);
		if(t_currentDirPath!="")
		{
			t_currentDirPath=t_currentDirPath.replace('\\','/');
		if(t_currentDirPath.at(t_currentDirPath.length()-1)=='/')
			t_currentDirPath=t_currentDirPath.left(t_currentDirPath.length()-1);
		j_startDirsPath << t_currentDirPath;
		}
		}
	}
}

void JulyScanDir::setFilesFilter(QString filter)
{
	j_filesFilter=filter.split(";;");
}

void JulyScanDir::setFilesFilter(QStringList filters)
{
	j_filesFilter=filters;
}

void JulyScanDir::setSearchSubFolders(bool t_on)
{
	j_canSearchSubFolders=t_on;
}
// End Prepare Functions


void JulyScanDir::j_endSearching()
{
	if(j_filesList.size()>0)
	emit loadedList(j_filesList);
	else emit errorHeppend(0);
	j_startDirsPath.clear();
	j_currentFileNum=0;
	j_filesList.clear();
	j_canSearchSubFolders=true;
	emit fileChanged("");
}

void JulyScanDir::run()
{
	emit fileChanged("");
	emit numChanged(0);
	for(int t_n=0;t_n<j_startDirsPath.size();t_n++)
	j_filesList+=j_listFromDir(j_startDirsPath.at(t_n));
	j_endSearching();
}

void JulyScanDir::scanDir(QString dirName,QStringList filterList, bool subOn)
{
	setStartDir(dirName);
	setFilesFilter(filterList);
	setSearchSubFolders(subOn);
	scanDir();
}

void JulyScanDir::scanDir(QStringList dirName,QStringList filterList, bool subOn)
{
	setStartDirs(dirName);
	setFilesFilter(filterList);
	setSearchSubFolders(subOn);
	scanDir();
}

void JulyScanDir::scanDir(QString dirName,QString filter, bool subOn)
{
	setStartDir(dirName);
	setFilesFilter(filter);
	setSearchSubFolders(subOn);
	scanDir();
}

void JulyScanDir::scanDir(QStringList dirName,QString filter, bool subOn)
{
	setStartDirs(dirName);
	setFilesFilter(filter);
	setSearchSubFolders(subOn);
	scanDir();
}

QStringList JulyScanDir::getStartDirNames()
{
	return j_startDirsPath;
}

void JulyScanDir::waitForFinished()
{
	while(isRunning());
}

void JulyScanDir::scanDir()
{
	bool t_existStartDirs=true;
	for(int t_n=0;t_n<j_startDirsPath.size();t_n++)
		if(!QFile::exists(j_startDirsPath.at(t_n)))
			t_existStartDirs=false;
	if(!t_existStartDirs)
		emit errorHeppend(1);
		else
	if(!isRunning()) start();
}

QStringList JulyScanDir::j_listFromDir(QString j_startDirPath)
{
bool t_canScanThisDir=true;

if(j_isIgnoreDirsEnabled)
	if(j_ignoreDirsList.contains(j_startDirPath,Qt::CaseInsensitive))t_canScanThisDir=false;

QStringList result;
if(t_canScanThisDir)
{
	QDir thisDir(j_startDirPath);
	thisDir.setSorting(QDir::Name);
	if(thisDir.exists())
	{
		QDir::Filters t_filters=QDir::NoSymLinks | QDir::NoDotAndDotDot;
		if(j_isSearchingHidden)t_filters=t_filters | QDir::Hidden;
		QStringList Files = thisDir.entryList(j_filesFilter,QDir::Files | t_filters);
		QStringList Directorys = thisDir.entryList(QDir::Dirs | t_filters);

if(j_canSearchSubFoldersFirst && j_canSearchSubFolders)
		for(int n=0;n<Directorys.size();n++)
			result << j_listFromDir(j_startDirPath+"/"+Directorys.at(n));

		for(int n=0;n<Files.size();n++)
		{
			bool t_acceptedResult=true;
			if(j_isRegExpEnabled)
				t_acceptedResult=j_compareRegExp.exactMatch(Files.at(n));
			if(t_acceptedResult)
			{
			result << j_startDirPath+"/"+Files.at(n);
			j_currentFileNum++;
			emit fileChanged(result.last());
			emit fileChanged(QFileInfo(result.last()));
			emit numChanged(j_currentFileNum);
			}
		}

if(!j_canSearchSubFoldersFirst && j_canSearchSubFolders)
		for(int n=0;n<Directorys.size();n++)
			result << j_listFromDir(j_startDirPath+"/"+Directorys.at(n));

		emit dirChanged(j_startDirPath);
	}
}
	return result;
}

int JulyScanDir::getCurrentFileNum()
{
	return j_currentFileNum;
}

void JulyScanDir::stopSearching()
{
	if(isRunning())
	{
	terminate();
	quit();
	wait();
	j_endSearching();
	}
}

void JulyScanDir::setRegExp(QRegExp t_regExp)
{
	j_compareRegExp=t_regExp;
	j_isRegExpEnabled=true;
}

void JulyScanDir::clearRegExp()
{
	j_isRegExpEnabled=false;
	j_compareRegExp=QRegExp();
}

void JulyScanDir::setIgnoreDirs(QStringList t_list)
{
	if(!isRunning())
	{
	j_ignoreDirsList.clear();
		for(int t_n=0;t_n<t_list.size();t_n++)
		{
		QString t_currentDirPath=t_list.at(t_n);
		if(t_currentDirPath!="")
		{
				t_currentDirPath=t_currentDirPath.replace('\\','/');
		if(t_currentDirPath.at(t_currentDirPath.length()-1)=='/')
			t_currentDirPath=t_currentDirPath.left(t_currentDirPath.length()-1);
		j_ignoreDirsList << t_currentDirPath;
		}
		}
	if(j_ignoreDirsList.size()>0)j_isIgnoreDirsEnabled=true;
	}
}

void JulyScanDir::setIgnoreDirs(QString t_list)
{
	setIgnoreDirs(t_list.split(";;"));
}

void JulyScanDir::clearIgnoreDirs()
{
	j_isIgnoreDirsEnabled=false;
	j_ignoreDirsList.clear();
}

void JulyScanDir::setSearchHidden(bool hidden)
{
	j_isSearchingHidden=hidden;
}
// Created By JULY IGHOR
