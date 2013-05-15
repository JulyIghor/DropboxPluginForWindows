// Created By July IGHOR JulyAbout v1.02

#include "julyabout.h"

JulyAbout::JulyAbout(QWidget *parent,QString title, QString text, QString urlText,QString logoPath)
	: QWidget(parent)
{
	resize(400,360);
	currentAllpha=0;
	maxAlpha=80;
	setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::SplashScreen);
	setWindowOpacity((double)currentAllpha/100);
	timerAlpha = new QTimer(this);
	connect(timerAlpha,SIGNAL(timeout()),this,SLOT(addAlpha()));

// Create Background
	fon = new QLabel(this);
	fon->setGeometry(0,0,size().width(),size().height());
	fon->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #0077ff, stop: 1 #ffff00); border-radius: 25px; border: 2px solid black;");
	QRectF rectangle(this->rect());
	QPixmap pixmap(this->width(),this->height());
	pixmap.fill(Qt::transparent);
         QPainter painter(&pixmap);
		 painter.setPen(Qt::red);
		 painter.setBrush(Qt::red);
		 rectangle.setLeft(-1);
		 rectangle.setTop(-1);
         painter.drawRoundedRect(rectangle, 26.0, 26.0);
		 setMask(pixmap.mask()); 
// End Create Background



	int currentPos=0;
		 if(QFile::exists(logoPath))
		 {
		 logoLabel = new QLabel(this);
		 logoLabel->setGeometry(4,4,80,80);
		 logoLabel->setScaledContents(true);
		 logoLabel->setPixmap(QPixmap(logoPath));
		 currentPos=88;
		 }

		 if(title!="")
		 {
		 titleLabel = new QLabel(this);
		 titleLabel->setGeometry(currentPos+4,4,geometry().width()-currentPos-8,84);
		 titleLabel->setAlignment(Qt::AlignCenter);
		 QFont fnt;
		 fnt.setFamily("Arial");
		 fnt.setPixelSize(24);
		 titleLabel->setFont(fnt);
		 titleLabel->setText(title);
		 currentPos=90;
		 }else currentPos=4;

		 if(text!="")
		 {
		 textLabel = new QLabel(this);
		 textLabel->setGeometry(4,currentPos,geometry().width()-8,120);
		 textLabel->setAlignment(Qt::AlignCenter);
		 QFont fnt;
		 fnt.setFamily("Comic Sans MS");
		 fnt.setPixelSize(20);
		 textLabel->setFont(fnt);
		 textLabel->setWordWrap(true);
		 textLabel->setText(text);
		 currentPos=currentPos+textLabel->height();
		 }

		 urlLabel = new JulyUrl(this,4,currentPos,geometry().width()-8,80,urlText);
		 connect(urlLabel,SIGNAL(linked()),this,SLOT(hideAbout()));
		 OKButton = new QPushButton(this);
		 OKButton->resize(100,50);
		 OKButton->setText("OK");
		 OKButton->setFocusPolicy(Qt::NoFocus);
		 OKButton->move((geometry().width()-100)/2,geometry().height()-70);
		 OKButton->setStyleSheet("QPushButton {"
     "border: 2px solid black;"
     "border-radius: 10px;"
	 "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ff0000, stop: 1 #990000);"
	 "font: 40px bold \"Arial Black\"; color: white;}"
     "QPushButton:pressed { background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
     "stop: 0 #ff0000, stop: 1 #550000);}"
     "QPushButton:flat {border: none;}"
     "QPushButton:default {border-color: black;}");
		 connect(OKButton,SIGNAL(clicked()),this,SLOT(hideAbout()));
		 connect(OKButton,SIGNAL(pressed()),this,SLOT(okPressd()));
		 canDrug=true;
		 timerAlpha->start(20);
		 	started=true;
}

JulyAbout::~JulyAbout()
{
}

void JulyAbout::okPressd()
{
	canDrug=false;
}

void JulyAbout::showAbout()
{
	QRect mWindow=parentWidget()->geometry();
	move((mWindow.width()-geometry().width())/2+mWindow.left(),(mWindow.height()-geometry().height())/2+mWindow.top());
canDrug=true;
	show();
timerAlpha->start(20);
}

void JulyAbout::addAlpha()
{
	if(started)
	{
	currentAllpha-=funcAnim(currentAllpha);
	if(currentAllpha<0)
	{
		timerAlpha->stop();
		started=false;
		currentAllpha=0;
		hide();
		urlLabel->reSet();
	}
	move(geometry().x(),geometry().y()+funcAnim(currentAllpha));
	}
	else
	{
	urlLabel->Start();
	currentAllpha+=funcAnim(currentAllpha);
	if(currentAllpha>maxAlpha)
	{
		timerAlpha->stop();
		started=true;
		currentAllpha=maxAlpha;
	}
	move(geometry().x(),geometry().y()+funcAnim(currentAllpha));
	}
	setWindowOpacity((double)currentAllpha/100);
}
void JulyAbout::closeEvent(QCloseEvent *event)
{
	event->ignore();
	timerAlpha->start(20);
}

void JulyAbout::hideAbout()
{
	timerAlpha->start(20);
}

void JulyAbout::mousePressEvent(QMouseEvent *event)
{
	canDrug=true;
	event->accept();
    if (event->button() == Qt::LeftButton)
        dragPosition = event->globalPos() - frameGeometry().topLeft();
}

void JulyAbout::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton) if(canDrug) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}


int JulyAbout::funcAnim(int val)
{
	int rez=sin((double)(maxAlpha-val)/(maxAlpha-20))*30;
	if(rez==0)rez=1;
	return rez;
}

void JulyAbout::keyPressEvent(QKeyEvent *e)
{
	e->accept();
	hideAbout();
}