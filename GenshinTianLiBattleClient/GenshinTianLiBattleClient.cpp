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
	//long sslLibraryBuildVersionNumber()		// 返回编译时SSL(静态库)版本号
	//QString sslLibraryBuildVersionString()	// 返回编译时SSL(静态库)版本字符串
	//long sslLibraryVersionNumber()			// 返回运行时SSL库版本号
	//QString sslLibraryVersionString()		// 返回运行时SSL库版本字符串
	//bool supportsSsl()						// 返回是否支持SSL true支持/false不支持
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
	// 0 弹窗提示下载


	/*
	// 更新自己
	// 1. 下载更新包
	// 2. 解压更新包
	// 3. 重命名自己
	// 4. 拷贝新版本到这里并重命名
	// 5. 关闭并删除自己，打开新版本
	
	// 1. 下载更新包
	QNetworkRequest request;
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	request.setUrl(QUrl(updata_pkg_url));
	QNetworkReply* reply = manager->get(request);
	connect(reply, &QNetworkReply::finished, [=]() {
		if (reply->error() == QNetworkReply::NoError) {
			QByteArray bytes = reply->readAll();
			// 写入到文件
			QFile file("update.zip");
			file.open(QIODevice::WriteOnly);
			file.write(bytes);
			file.close();
			qDebug() << file.fileName();
			// 输出当前目录
			qDebug() << QDir::currentPath();

			
			// 2. 解压更新包
			QZipReader reader("update.zip");
			reader.extractAll(QDir::currentPath());
			
			// 3. 重命名自己
			QFile::rename(QDir::currentPath()+"/GenshinTianLiBattleClient.exe", "GenshinTianLiBattleClient_new.exe");

			// 4. 拷贝新版本到这里并重命名
			//QFile::copy(QDir::currentPath() + "/GenshinTianLiBattleClient_new.exe", QDir::currentPath() + "/GenshinTianLiBattleClient.exe");
			
			
			

		}
		else {
			qDebug() << reply->errorString();
		}
		});
	*/
}
