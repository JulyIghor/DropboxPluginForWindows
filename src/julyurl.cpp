// Created By July IGHOR JulyURL v1.01

#include "julyurl.h"
#include <QPainter>
#include <QFontMetrics>
JulyUrl::JulyUrl(QWidget *parent, int x, int y, int w, int h, QString link)
	: QLabel(parent)
{
	startRect=QRect(x,y,w,h);
	setGeometry(startRect);
	zoomTimer = new QTimer(this);
	connect(zoomTimer,SIGNAL(timeout()),this,SLOT(zoom()));
	udNormalFont=0;
	isAnimating=false;
	add=2;
	text=link;;
	QFont font;
	font.setFamily("Arial");
	font.setPixelSize(46);
	font.setStretch(60);
	double textWidth=QFontMetrics(font).width(link);
	pixmap1 = QPixmap(400,100);
	pixmap1.fill(Qt::transparent);
	QPainter painter(&pixmap1);
	painter.setPen(Qt::blue);
	painter.setFont(font);
	painter.drawText(QRectF(0,0,400,100),Qt::AlignCenter,text);
	pixmap2=pixmap1;
	QPixmap line(textWidth,4);
	line.fill(Qt::blue);
	painter.drawPixmap((400-textWidth)/2,84,line);
	setPixmap(pixmap1);
	notPressing=true;
	setScaledContents(true);	
}

void JulyUrl::mousePressEvent(QMouseEvent *event)
{
	QLabel::mouseMoveEvent(event);
	if(event->button()==Qt::LeftButton)
	{
		move=event->pos();
		setPixmap(pixmap2);
		notPressing=false;
	}
}

void JulyUrl::mouseMoveEvent(QMouseEvent *event)
{
	QLabel::mouseMoveEvent(event);
	if(abs(move.x()-event->x())>10)notPressing=true;
	if(abs(move.y()-event->y())>10)notPressing=true;
	if(notPressing)setPixmap(pixmap1);
}

void JulyUrl::mouseReleaseEvent(QMouseEvent *event)
{
	QLabel::mouseMoveEvent(event);
	if(event->button()==Qt::LeftButton)
	{
		setPixmap(pixmap1);
		if(!notPressing)
		{
		emit linked();
		QDesktopServices::openUrl(QUrl("http://"+text));
		notPressing=true;
		}
	}
}

JulyUrl::~JulyUrl()
{

}

void JulyUrl::Start()
{
if(!isAnimating){isAnimating=true;zoomTimer->start(40);}
}

void JulyUrl::reSet()
{
	zoomTimer->stop();
	udNormalFont=0;
	isAnimating=false;
}

void JulyUrl::zoom()
{
setGeometry(startRect.left()+udNormalFont,startRect.top()+udNormalFont,startRect.width()-udNormalFont*2,startRect.height()-udNormalFont*2);
udNormalFont+=add;
if(udNormalFont>20)add=-2;
if(udNormalFont<0)add=2;
}