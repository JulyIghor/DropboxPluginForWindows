// Created By July IGHOR. Please do not remove this line :)

#ifndef DROPBOXPLUGIN_H
#define DROPBOXPLUGIN_H

#include <QtGui/QWidget>
#include "ui_dropboxplugin.h"
#include "julyabout.h"
#include <QKeyEvent>
#include <QClipboard>
#include <QProcess>

class DropboxPlugin : public QWidget
{
	Q_OBJECT

public:
	QPoint dragPosition;
	bool isDropboxv12x;
	bool isDragged;
	QString getMyDropboxDir();
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void insertIDFromClipboard(int key);
	void keyPressEvent(QKeyEvent *event);
	QStringList Language;
	QString mySelf;
	QString getMyDropboxFolder();
	void setMyDropboxFolder(QString);
	void clearOldSettings();
	JulyAbout *aboutWindow;
	DropboxPlugin(QWidget *parent = 0, Qt::WFlags flags = 0);
private:
	Ui::DropboxPluginClass ui;

private slots:
	void copyDonataButton();
	void whatIsBitcoin();
	void on_shortcutForMove_clicked();
	void on_shortcutForCopy_clicked();
	void on_insertFromClipboard_clicked();
	void on_whatThis_clicked();
	void on_userID_textChanged(const QString &);
	void on_brouseDropboxDir_clicked();
	void on_buttonSave_clicked();
	void on_buttonAbout_clicked();
};

#endif // DROPBOXPLUGIN_H
