// Created By July IGHOR JulyURL v1.01

#ifndef JULYURL_H
#define JULYURL_H

#include <QLabel>
#include <QFont>
#include <QMouseEvent>
#include <QTimer>
#include <QDesktopServices>
#include <QUrl>

class JulyUrl : public QLabel
{
	Q_OBJECT

public:
	int add;
	bool isAnimating;
	QPoint move;
	QPixmap pixmap1;
	QPixmap pixmap2;
	QString text;
	QRect startRect;
	int udNormalFont;
	void Start();
	void reSet();
	QTimer *zoomTimer;
	bool notPressing;
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	JulyUrl(QWidget *parent, int x, int y, int w, int h, QString t);
	~JulyUrl();
signals:
	void linked();
public slots:
	void zoom();
};

#endif // JULYURL_H
