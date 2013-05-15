// Created By July IGHOR. Please do not remove this line :)

#include "dropboxplugin.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDesktopWidget>
#include <QMouseEvent>
#include <QSettings>
#include <QTextStream>
#include <QProcess>
#include <QSettings>
#include "qtwin.h"
#include "Shlobj.h"
#include <QApplication>
#include <QDateTime>

DropboxPlugin::DropboxPlugin(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	isDropboxv12x=false;
	isDragged=false;

	QString version="Dropbox Plugin v1.7";
mySelf=QCoreApplication::applicationFilePath();

	ui.setupUi(this);
	setWindowTitle(version);
	
	QStringList uaLanguage;
	QStringList ruLanguage;

uaLanguage << "Творець програми July Ighor\nРозробка веб-сайтів та програмного забезпечення"
<< "Попередження"
<< "Налаштування Dropbox"
<< "Будь-ласка введіть ID"
<< "Налаштування збережені. Просто перетягніть файли на програму або скористайтеся контекстним меню провідника. В результаті файли будуть копійовані в папку Public в Dropbox а всі посилання на них будуть копійовані в буфер обміну. Не переміщуйте програму для коректної роботи"
<< "Папка даних Dropbox:"
<< "ID користувача:"
<< "При копіювання зовнішнього посилання на файл Dropbox в папці Public ви бачите YOUR_ID (\"http://dl.dropboxusercontent.com/u/YOUR_ID/File.jpg\")"
<< "Показувати в провіднику"
<< "Про програму"
<< "Зберегти"
<< "Огляд"
<< "Dropbox: копіювати в Public"
<< "Dropbox: перемістити в Public"
<< "Dropbox не встановлено. Спочатку потрібно встановити програму www.dropbox.com"
<< "Оберіть папку де розташовані файли Dropbox"
<< "Dropbox - копіювати в Public"
<< "Dropbox - перемістити в Public"
<< "Надіслати на робочий стіл – створити посилання для копіювання файлів"
<< "Надіслати на робочий стіл – створити посилання для переміщення файлів"
<< "Вставити з буфера"
<< "Посилання успішно створене на робочому столі"
<< "Налаштування програми"
<< "Перевіряти оновлення"
<< "Звукові ефекти"
<< "Будь-ласка вкажіть існуючу папку Dropbox"
<< "Підпапка Dropbox\\Public"
<< "Формат посилання"
<< "Bictoin адресу копійовано до буферу обміну.\n\nДякуємо за підтримку!"
<< "http://ru.wikipedia.org/wiki/Bitcoin"
<< "Копіювати";


ruLanguage << "Создатель July Ighor\nРазработка веб-сайтов и програмного обеспечения"
<< "Предупреждение"
<< "Настройки Dropbox"
<< "Пожалуйста введите ID"
<< "Настройки сохранены. Просто перетащите файлы на програму или используйте контекстное меню проводника. В результате файлы будут копированы в папку Public в Dropbox и все ссылки на них будут в буфере обмена. Не перемещяйте файл программы для корректной работы."
<< "Папка данных Dropbox:"
<< "ID пользователя:"
<< "При копировании внешней ссылки на файл Dropbox в папке Public вы увидете YOUR_ID (\"https://dl.dropboxusercontent.com/u/YOUR_ID/File.jpg\")"
<< "Показывать в проводнике"
<< "О программе"
<< "Сохранить"
<< "Обзор"
<< "Dropbox: копировать в Public"
<< "Dropbox: переместить в Public"
<< "Dropbox не установлено. Сначала установите программу www.dropbox.com"
<< "Выберите папку где храняться файлы Dropbox"
<< "Dropbox - копировать в Public"
<< "Dropbox - переместить в Public"
<< "Отправить на рабочий стол – создать ссылку для копирования файлов"
<< "Отправить на рабочий стол – создать ссылку для перемещения файлов"
<< "Вставить из буфера"
<< "Ссылка успешно создана на рабочем столе"
<< "Настройки программы"
<< "Проверять обновления"
<< "Звуковые еффекты"
<< "Пожалуйста укажите существующую папку Dropbox"
<< "Подпапка Dropbox\\Public"
<< "Формат ссылки"
<< "Bitcoin адрес копирован в буфер обмена.\n\nСпасибо за поддержку!"
<< "http://ru..wikipedia.org/wiki/Bitcoin"
<< "Копировать";

Language << "Created by July Ighor\nThe Best Software and Web Development"
<< "Warning"
<< "Dropbox Settings"
<< "Please enter user ID"
<< "Settings saved. Just Drag files on the program or use context menu of Explorer. As a result files will be copyed in to the Public folder in Dropbox and all links to them will be copyed to Clipboard. Do not move exe file to make it works."
<< "Dropbox data folder:"
<< "User ID:"
<< "When you copy Dropbox global address (\"https://dl.dropboxusercontent.com/u/YOUR_ID/File.jpg\")"
<< "Show in context Menu"
<< "About"
<< "Save"
<< "Browse"
<< "Dropbox: copy to Public"
<< "Dropbox: move to Public"
<< "Dropbox is not installed. Install software first www.dropbox.com"
<< "Chuse new folder for Dropbox files"
<< "Dropbox - Copy to Public"
<< "Dropbox - Move to Public"
<< "Send to Desktop – Create Symlink to Copy file"
<< "Send to Desktop – Create Symlink to Move file"
<< "Paste URL"
<< "Created a symbolic link on Desktop"
<< "General Settings"
<< "Check for updates"
<< "Enable sound effects"
<< "Please chuse existing Dropbox folder before saving"
<< "Dropbox\\Public Sub Directory"
<< "URL Format"
<< "Bitcoin address copied to clipboard.\n\nThank you for your Support!"
<< "http://en.wikipedia.org/wiki/Bitcoin"
<< "Copy";

		QLocale count;
		if(count.language()==QLocale::Ukrainian)Language=uaLanguage;
		if(count.language()==QLocale::Russian)Language=ruLanguage;

	ui.dropboxSetup->setTitle(Language.at(2));

	ui.shortcutForCopy->setToolTip(Language.at(18));
	ui.shortcutForMove->setToolTip(Language.at(19));

ui.insertFromClipboard->setText(Language.at(20));
ui.label->setText(Language.at(5));
ui.label_2->setText(Language.at(6));
ui.userID->setToolTip(Language.at(7));
ui.showContext->setText(Language.at(12));
ui.showContextMove->setText(Language.at(13));
ui.buttonAbout->setText(Language.at(9));
ui.buttonSave->setText(Language.at(10));
ui.brouseDropboxDir->setText(Language.at(11));
ui.groupBoxExplorer->setTitle(Language.at(8));
ui.groupSettings->setTitle(Language.at(22));
ui.checkUpdates->setText(Language.at(23));
ui.checkSound->setText(Language.at(24));
ui.subDirectoryGroupBox->setTitle(Language.at(26));
ui.groupBox->setTitle(Language.at(27));
ui.copyDonateButton->setText(Language.at(30));

	setWindowFlags(Qt::WindowCloseButtonHint|Qt::WindowMinimizeButtonHint|Qt::MSWindowsFixedSizeDialogHint);
	aboutWindow = new JulyAbout(this,version,Language.at(0),"www.gigasoftgroup.com",":/Resources/GigaSOFTLogo.png") ;
	//resize(minimumSizeHint());
	move((QApplication::desktop()->screenGeometry().width()-this->width())/2,(QApplication::desktop()->screenGeometry().height()-this->height())/2);

QSettings settings("JulySoft©","Dropbox Plugin");
		ui.userID->setText(settings.value("MyDropboxID","").toString());
		ui.showContext->setChecked(settings.value("isInContextMenu",true).toBool());
		ui.showContextMove->setChecked(settings.value("isInContextMenuMove",true).toBool());

		ui.checkUpdates->setChecked(settings.value("canCheckUpdates",true).toBool());
		ui.checkSound->setChecked(settings.value("isSoundEnabled",true).toBool());
		ui.subDirEdit->setText(settings.value("SubDir","").toString());

		clearOldSettings();

	QString dropboxDir=settings.value("MyDropboxDir","").toString().replace("/","\\");

	ui.dropBoxDir->setText(getMyDropboxDir());
    if(QtWin::isCompositionEnabled())
	{
		QtWin::extendFrameIntoClientArea(this);
		this->setStyleSheet("QGroupBox {background: rgba(255,255,255,160); border: 1px solid gray;border-radius: 3px;margin-top: 7px;} QGroupBox:title {background: qradialgradient(cx: 0.5, cy: 0.5, fx: 0.5, fy: 0.5, radius: 0.7, stop: 0 #fff, stop: 1 transparent); border-radius: 2px; padding: 1 4px; top: -7; left: 7px;}");
	}
	setFixedSize(minimumSize());

	if(settings.value("canCheckUpdates",true).toBool()&&(settings.value("lastUpdateCheck",QDate()).toDate()!=QDate::currentDate()))
	{
		QProcess proc;
		proc.startDetached(QCoreApplication::applicationFilePath(),QStringList("/update"));
		proc.waitForStarted();
		settings.setValue("lastUpdateCheck",QDate::currentDate());
	}
}

void DropboxPlugin::copyDonataButton()
{
	QApplication::clipboard()->setText(ui.bitcoinAddress->text());
	QMessageBox::information(this,this->windowTitle(),Language.at(28));
}

void DropboxPlugin::whatIsBitcoin()
{
	QDesktopServices::openUrl(QUrl(Language.at(29)));
}

void DropboxPlugin::clearOldSettings()
{
	QSettings shellSettings("HKEY_CLASSES_ROOT\\*\\shell\\",QSettings::NativeFormat);
	if(shellSettings.value("JulyDropboxPlugin/Default","").toString()!="")shellSettings.remove("JulyDropboxPlugin");
	if(shellSettings.value("JulyDropboxPluginMove/Default","").toString()!="")shellSettings.remove("JulyDropboxPluginMove");
}

QString DropboxPlugin::getMyDropboxDir()
{
QSettings settings("JulySoft©","Dropbox Plugin");
	QByteArray result;
	QString dbPath=QSettings("HKEY_CURRENT_USER\\Software\\Dropbox",QSettings::NativeFormat).value("InstallPath").toString().replace("\\bin","");
	if(QFile::exists(dbPath+"\\host.dbx"))dbPath+="\\host.dbx";
	else dbPath+="\\host.db";
	QFile readDb(dbPath);
	if(readDb.open(QIODevice::ReadOnly|QIODevice::Text))
	{
		result=QByteArray::fromBase64(readDb.readAll().split('\n').last()).replace('\\','/');
		readDb.close();
	}
	if(!QFile::exists(result+"\\Public"))
		result=settings.value("MyDropboxDir","").toString().replace("\\","/").toAscii();
	if(!QFile::exists(result+"\\Public"))
	{
		QStringList findDropboxPublic;
		findDropboxPublic<<QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation).replace('/','\\')+"\\Dropbox"<<QDesktopServices::storageLocation(QDesktopServices::HomeLocation).replace('/','\\')+"\\Dropbox"<<"C:\\Dropbox"<<"D:\\Dropbox"<<"E:\\Dropbox";
		for(int n=0;n<findDropboxPublic.count();n++)
		if(QFile::exists(findDropboxPublic.at(n)+"\\Public"))
		{
			result=findDropboxPublic.at(n).toAscii();
			break;
		}
	}
	result.replace('/','\\');
	return result;
}

void DropboxPlugin::on_buttonAbout_clicked()
{
	aboutWindow->showAbout();
}

void DropboxPlugin::on_buttonSave_clicked()
{
	if(ui.userID->text()==""){QMessageBox::information(this,Language.at(1),Language.at(3));return;}
	if(QFile::exists(ui.dropBoxDir->text()+"\\Public"))
	{
	QSettings settings("JulySoft©","Dropbox Plugin");
		settings.setValue("MyDropboxID",ui.userID->text());
		settings.setValue("MyDropboxDIR",ui.dropBoxDir->text());
		settings.setValue("isInContextMenu",ui.showContext->isChecked());
		settings.setValue("isInContextMenuMove",ui.showContextMove->isChecked());
		settings.setValue("canCheckUpdates",ui.checkUpdates->isChecked());
		settings.setValue("isSoundEnabled",ui.checkSound->isChecked());
		settings.setValue("SubDir",ui.subDirEdit->text());
		settings.setValue("OldUrlStyle",ui.urlOldStyle->isChecked());

		QSettings shellSettings("HKEY_CURRENT_USER\\Software\\Classes\\*\\shell\\",QSettings::NativeFormat);
		if(ui.showContext->isChecked())
		{
			shellSettings.setValue("DropboxPlugin/Default",Language.at(12));
			shellSettings.setValue("DropboxPlugin/command/Default",QCoreApplication::applicationFilePath().replace('/','\\')+" \"%L\"");
		} else shellSettings.remove("DropboxPlugin");

		if(ui.showContextMove->isChecked())
		{
			shellSettings.setValue("DropboxPluginMove/Default",Language.at(13));
			shellSettings.setValue("DropboxPluginMove/command/Default",QCoreApplication::applicationFilePath().replace('/','\\')+" /move \"%L\"");
		} else shellSettings.remove("DropboxPluginMove");

		QMessageBox::information(this,this->windowTitle(),Language.at(4));
		QCoreApplication::quit();
	}
	else
	QMessageBox::information(this,Language.at(1),Language.at(25));
}

void DropboxPlugin::on_brouseDropboxDir_clicked()
{
	QString t_dirPath=QFileDialog::getExistingDirectory(this,Language.at(15),ui.dropBoxDir->text());
 if(t_dirPath!="")
	 if(QFileInfo(t_dirPath).isDir())
	 {
	 t_dirPath=t_dirPath.replace("/","\\");
	 if(t_dirPath.right(1)=="\\")t_dirPath=t_dirPath.left(t_dirPath.length()-1);
	 QSettings settings("JulySoft©","Dropbox Plugin");
		       settings.setValue("MyDropboxDir",t_dirPath);
	 ui.dropBoxDir->setText(t_dirPath);
	 }
}

void DropboxPlugin::on_userID_textChanged(const QString &str)
{
	QString newStr;
	for(int n=0;n<str.length();n++)
		if(str.at(n).isDigit())newStr+=str.at(n).toAscii();
	ui.userID->setText(newStr);
}

void DropboxPlugin::keyPressEvent(QKeyEvent *event)
{
	insertIDFromClipboard(event->key()); 
	event->accept();
}

void DropboxPlugin::insertIDFromClipboard(int key)
{
if((QApplication::keyboardModifiers()==Qt::ControlModifier)&&(key==Qt::Key_V))
	on_insertFromClipboard_clicked();
}

void DropboxPlugin::on_whatThis_clicked()
	{QMessageBox::information(this,this->windowTitle(),ui.userID->toolTip());}

void DropboxPlugin::on_insertFromClipboard_clicked()
{
	QString clipboard=QApplication::clipboard()->text();
	int a=clipboard.indexOf("/u/");
	if(a==-1){on_whatThis_clicked();return;}
	a+=3;
	int b=clipboard.indexOf("/",a);
	if(b==-1){on_whatThis_clicked();return;}
	QString uId;
	for(int n=a;n<b;n++)if(clipboard.at(n).isDigit())uId.append(clipboard.at(n));
	if(uId.isEmpty()){on_whatThis_clicked();return;}
	ui.userID->setText(uId);
}

void DropboxPlugin::mousePressEvent(QMouseEvent *event)
{
	event->accept();
    if (event->button() == Qt::LeftButton)
	{
        dragPosition = event->globalPos() - frameGeometry().topLeft();
		isDragged=true;
	}
}

void DropboxPlugin::mouseReleaseEvent(QMouseEvent *event)
{
	event->accept();
	isDragged=false;
}

void DropboxPlugin::mouseMoveEvent(QMouseEvent *event)
{
	if(isDragged && event->buttons() & Qt::LeftButton) 
	{
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

bool createShortcut(QString filePath, QString symLinkPath, QString description, QString workDirectory="", QString arguments="")
{
    HRESULT hres; 
    IShellLink* psl; 
 
    hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,IID_IShellLink, (LPVOID*)&psl); 
    if(SUCCEEDED(hres)) 
    { 
        IPersistFile* ppf; 
        psl->SetPath(filePath.utf16()); 
        psl->SetDescription(description.utf16());
		if(!arguments.isEmpty())psl->SetArguments(arguments.utf16());
		if(!workDirectory.isEmpty())psl->SetWorkingDirectory(workDirectory.utf16());
		hres=psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf); 
        if(SUCCEEDED(hres)) 
        { 
            WCHAR wsz[MAX_PATH]; 
			MultiByteToWideChar(CP_ACP, 0, (LPCSTR)symLinkPath.toAscii(), -1, wsz, MAX_PATH);
            hres = ppf->Save(wsz, TRUE); 
            ppf->Release(); 
        } 
        psl->Release(); 
    }
	return SUCCEEDED(hres);
}

void DropboxPlugin::on_shortcutForCopy_clicked()
{
	createShortcut(QApplication::applicationFilePath().replace('/','\\') ,QDesktopServices::storageLocation(QDesktopServices::DesktopLocation).replace('/','\\')+"\\"+Language.at(16)+".lnk","Created by "+this->windowTitle(),QApplication::applicationDirPath().replace('/','\\'),"");
	QMessageBox::information(0,this->windowTitle(),Language.at(21));
}

void DropboxPlugin::on_shortcutForMove_clicked()
{
	createShortcut(QApplication::applicationFilePath().replace('/','\\') ,QDesktopServices::storageLocation(QDesktopServices::DesktopLocation).replace('/','\\')+"\\"+Language.at(17)+".lnk","Created by "+this->windowTitle(),QApplication::applicationDirPath().replace('/','\\'),"/move");
	QMessageBox::information(0,this->windowTitle(),Language.at(21));
}