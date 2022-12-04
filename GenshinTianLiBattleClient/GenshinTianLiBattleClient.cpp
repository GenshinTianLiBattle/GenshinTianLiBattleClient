#include "GenshinTianLiBattleClient.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QString>
#include <qDebug>
#include <QLabel>
#include <QFile>
#include <QEventLoop>
#include <QDir>

#include "def/api/Api.h" // This is the header file that contains the URL

#include <QtGui/private/QZipReader_p.h>
#include <QtGui/private/QZipWriter_p.h>

#include <QSslSocket>





QString GenshinTianLiBattleClient::GetVersion()
{
	QNetworkRequest request;
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	request.setUrl(QUrl(tl::bettle::api::version_url));

	QNetworkReply* reply = manager->get(request);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

	QByteArray replyData = reply->readAll();
	reply->deleteLater();
	reply = nullptr;
	
	return replyData;
}

QString GenshinTianLiBattleClient::GetDownloadLink()
{
	QNetworkRequest request;
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	request.setUrl(QUrl(tl::bettle::api::download_url));

	QNetworkReply* reply = manager->get(request);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

	QByteArray replyData = reply->readAll();
	reply->deleteLater();
	reply = nullptr;
	
	return replyData;
}



GenshinTianLiBattleClient::GenshinTianLiBattleClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	
	manager = new QNetworkAccessManager(this);
	
	QLabel* label = new QLabel(this);
	label->setGeometry(0, 0, this->width(), this->height());
	label->setText("wait api");
	
	QString version = GetVersion();
	label->setText(version);
	QString download_link = GetDownloadLink();
	label->setText(download_link);
	UpdateSelf(download_link);

	// ssl
	//long sslLibraryBuildVersionNumber()		// ���ر���ʱSSL(��̬��)�汾��
	//QString sslLibraryBuildVersionString()	// ���ر���ʱSSL(��̬��)�汾�ַ���
	//long sslLibraryVersionNumber()			// ��������ʱSSL��汾��
	//QString sslLibraryVersionString()		// ��������ʱSSL��汾�ַ���
	//bool supportsSsl()						// �����Ƿ�֧��SSL true֧��/false��֧��
	qDebug() << QSslSocket::sslLibraryBuildVersionNumber();
	qDebug() << QSslSocket::sslLibraryBuildVersionString();
	qDebug() << QSslSocket::sslLibraryVersionNumber();
	qDebug() << QSslSocket::sslLibraryVersionString();
	qDebug() << QSslSocket::supportsSsl();

}

GenshinTianLiBattleClient::~GenshinTianLiBattleClient()
{
	manager->deleteLater();
	manager = nullptr;
}
void GenshinTianLiBattleClient::UpdateSelf(QString &updata_pkg_url)
{
	// 0 ������ʾ����


	/*
	// �����Լ�
	// 1. ���ظ��°�
	// 2. ��ѹ���°�
	// 3. �������Լ�
	// 4. �����°汾�����ﲢ������
	// 5. �رղ�ɾ���Լ������°汾
	
	// 1. ���ظ��°�
	QNetworkRequest request;
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	request.setUrl(QUrl(updata_pkg_url));
	QNetworkReply* reply = manager->get(request);
	connect(reply, &QNetworkReply::finished, [=]() {
		if (reply->error() == QNetworkReply::NoError) {
			QByteArray bytes = reply->readAll();
			// д�뵽�ļ�
			QFile file("update.zip");
			file.open(QIODevice::WriteOnly);
			file.write(bytes);
			file.close();
			qDebug() << file.fileName();
			// �����ǰĿ¼
			qDebug() << QDir::currentPath();

			
			// 2. ��ѹ���°�
			QZipReader reader("update.zip");
			reader.extractAll(QDir::currentPath());
			
			// 3. �������Լ�
			QFile::rename(QDir::currentPath()+"/GenshinTianLiBattleClient.exe", "GenshinTianLiBattleClient_new.exe");

			// 4. �����°汾�����ﲢ������
			//QFile::copy(QDir::currentPath() + "/GenshinTianLiBattleClient_new.exe", QDir::currentPath() + "/GenshinTianLiBattleClient.exe");
			
			
			

		}
		else {
			qDebug() << reply->errorString();
		}
		});
	*/
}
