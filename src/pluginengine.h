// Created By July IGHOR

#ifndef PLUGINENGINE_H
#define PLUGINENGINE_H

#include <QObject>
#include <QTimer>
#include <QStringList>
#include <QSettings>

class PluginEngine : public QObject
{
	Q_OBJECT

public:
	int interval;
	QTimer *timeOut;
	QString getMyDropboxDir();
	QString myDropboxDir;
	QString myDropboxID;
	QString dropboxUrl;
	QString subDir;
	QStringList Language;
	QStringList filesList;
	QSettings *settings;
	QStringList clipBoardLinks;
	void workAtArgumentList(QStringList);
	QStringList arguments;
	bool showSettings;
	PluginEngine(QStringList args);

private slots:
	void timeOutSlot();
	void reStartTimer();
public slots:
	void append(const QString&);
signals:
};

#endif // PLUGINENGINE_H
