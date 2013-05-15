// Created By July IGHOR JulyAbout v1.02

#ifndef JULYABOUT_H
#define JULYABOUT_H

#include <QWidget>
#include <QTimer>
#include <QCloseEvent>
#include <QLabel>
#include <QPainter>
#include <QBitmap>
#include <QPushButton>
#include "math.h"
#include <QFile>
#include <QKeyEvent>
#include "julyurl.h"

class JulyAbout : public QWidget
{
	Q_OBJECT

public:
	JulyUrl *urlLabel;
	QLabel *logoLabel;
	QLabel *titleLabel;
	QLabel *textLabel;
	QLabel *fon;
	QPushButton *OKButton;
	int funcAnim(int val);
	void showAbout();
	JulyAbout(QWidget *parent=0,QString title="", QString text="", QString urlText="", QString logoPath="");
	~JulyAbout();
	int currentAllpha;
	QTimer *timerAlpha;
	int maxAlpha;
	QPoint dragPosition;
	QPoint centerButton;
	bool started;
	bool canDrug;
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	void keyPressEvent(QKeyEvent *e);

public slots:
	void okPressd();
	void hideAbout();
	void addAlpha();
	
};

#endif // JULYABOUT_H
