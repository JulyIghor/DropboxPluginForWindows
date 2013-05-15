// Created By July IGHOR

#ifndef UPDATEVIEW_H
#define UPDATEVIEW_H

#include <QLabel>
#include <QHttp>

class UpdateView : public QLabel
{
	Q_OBJECT

public:
	QString imageData;
	QString tempFile;
	QHttp *http;
	QString getTegValue(QString *html, QString a, QString b);
	UpdateView(QWidget *param);
	~UpdateView();

private:
public slots:
	void loaded(bool);
private slots:
signals:
};

#endif // UPDATEVIEW_H
