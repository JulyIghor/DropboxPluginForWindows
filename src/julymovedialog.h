// Created By July IGHOR

#ifndef JULYMOVEDIALOG_H
#define JULYMOVEDIALOG_H

#include <QWidget>
#include "ui_julymovedialog.h"
#include "julyscandir.h"
#include <QMessageBox>

class JulyMoveDialog : public QWidget
{
	Q_OBJECT

public:
	bool wasDropboxStarted;
	QString copyErrorText;
	QString dropBoxAppFile;
	int replaceState;
	QStringList t_dirsList;
	QString lastOldDir;
	QString lastNewDir;
	QString startingText;
	QString processingMove;
	QString replaceAtempt;
	QString copyFinishedText;
	JulyScanDir *scanDir;
	void moveFolder(QString,QString);
	JulyMoveDialog(QWidget *parent = 0);
	~JulyMoveDialog();

private:
	Ui::JulyMoveDialogClass ui;

private slots:
void dirChanged(QString);      // Во время поиска возвращает полный адрес следующей директории
void fileChanged(QString);     // Во время поиска возвращает полный адрес текущего файла
void loadedList(QStringList);  // По завершению поиска возвращает список найденых файлов
void errorHeppend(int);        // Если случилась ошибка то возвращает: 0 если не найдено никаких файлов
                               // и 1 если заданая папка поиска не существует
public slots:
signals:
};

#endif // JULYMOVEDIALOG_H

