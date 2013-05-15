// JulySoft ScanDir Threaded Class v1.25
// Created By JULY IGHOR. Please do not edit this line :)

#ifndef JULYSCANDIR_H
#define JULYSCANDIR_H

#include <QThread>
#include <QStringList>
#include <QDir>
#include <QRegExp>
class JulyScanDir : public QThread
{
	Q_OBJECT

public:
// Prepare Functions
	void setSearchHidden(bool hidden);
	void setIgnoreDirs(QStringList);
	void setIgnoreDirs(QString);
	void clearIgnoreDirs();
	void setRegExp(QRegExp fileRegExp); // Set up File compare RegExp
	void clearRegExp();  // Clear and Disable File compare RegExp
	void setFilesFilter(QStringList filters); // Use this function to prepare search Files
	void setFilesFilter(QString filter);
	void setStartDir(QString dirName);
	void setStartDirs(QStringList dirsNames);
	void setSearchSubFolders(bool t_on); // Set To Search Files in Sub Folders
	void setSubFoldersFirst(bool t_on=true); // Uses for chuse metod of searching files
// End Prepare Functions

// Get Functions
	int getCurrentFileNum(); // Get Current Files Count
	QStringList getStartDirNames(); // Get Start Dir Name
// End Get Functions

// Scan Functions
	void scanDir(QString dirName,QStringList filterList=QStringList("*"), bool subOn=true); // Use this function to search Files
	void scanDir(QStringList dirName,QStringList filterList=QStringList("*"), bool subOn=true);
	void scanDir(QString dirName,QString filter, bool subOn=true); // Use this function to search Files
	void scanDir(QStringList dirName,QString filter, bool subOn=true);
	void scanDir(); // Use This Function after prepare search Files
	void waitForFinished(); // Uses for waiting while search finished
// End Scan Functions
	JulyScanDir(QObject *parent=0);
	~JulyScanDir();
public slots:
	void stopSearching(); // Terminate Searching Files
private:
	bool j_isSearchingHidden;
	bool j_isIgnoreDirsEnabled;
	QStringList j_ignoreDirsList;
	bool j_isRegExpEnabled;
	QRegExp j_compareRegExp;
	int j_currentFileNum;
	bool j_canSearchSubFolders;
	bool j_canSearchSubFoldersFirst;
	QStringList j_startDirsPath;
	QStringList j_filesList;
	QStringList j_filesFilter;
	QStringList j_listFromDir(QString j_startDirPath);
	void j_endSearching();
	void run();
signals:
	void dirChanged(QString); // Emit Full Dir Path when it changed
	void fileChanged(QString); // Emit Full File Path when it changed
	void fileChanged(QFileInfo); // Emit File size and other properties
	void numChanged(int); // Emit Files Count When it changed
	void loadedList(QStringList); // Emit QStringList All Files After Finished
	void errorHeppend(int); /* If some Error Heppend It emits:
								0: No Files Found
								1: Start Dir Not Exists*/
};

#endif // JULYSCANDIR_H

// Created By JULY IGHOR