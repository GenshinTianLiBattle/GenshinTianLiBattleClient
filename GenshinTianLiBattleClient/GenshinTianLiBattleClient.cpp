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
#include <QDialog>
#include <QProcess>

#include "def/api/Api.h" // This is the header file that contains the URL
#include "def/version/Version.h" // This is the header file that contains the version number

#include <QtGui/private/QZipReader_p.h>
#include <QtGui/private/QZipWriter_p.h>

#include <QSslSocket>

#include <Windows.h>

#pragma region 更新相关函数

#ifdef USE_QT_NET
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
#else
QString GenshinTianLiBattleClient::GetVersion()
{
	// curl
	QProcess curl;
	curl.start("curl", QStringList() << "-L" << tl::bettle::api::version_url);
	curl.waitForFinished();
	QString replyData = curl.readAll();
	return replyData;
}
#endif
#ifdef USE_QT_NET
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
#else
QString GenshinTianLiBattleClient::GetDownloadLink()
{
	// curl
	QProcess curl;
	curl.start("curl", QStringList() << "-L" << tl::bettle::api::download_url);
	curl.waitForFinished();
	QString replyData = curl.readAll();
	return replyData;
}
#endif
#ifdef USE_QT_NET
bool GenshinTianLiBattleClient::GetDownloadFile(QString url, QString path)
{
	QNetworkRequest request;
	request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
	request.setUrl(QUrl(url));

	QNetworkReply* reply = manager->get(request);
	QEventLoop eventLoop;
	connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
	eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

	QByteArray replyData = reply->readAll();
	reply->deleteLater();
	reply = nullptr;

	QFile file;

	file.setFileName(path + "/" + QUrl(url).fileName());
	if (!file.open(QIODevice::WriteOnly))
	{
		return false;
	}
	file.write(replyData);
	file.close();

	if (!file.exists())
	{
		return false;
	}
	return true;
}
#else
bool GenshinTianLiBattleClient::GetDownloadFile(QString url, QString path)
{
	// curl
	QProcess curl;
	curl.start("curl", QStringList() << "-L" << url << "-o" << path);
	curl.waitForFinished();

	if (curl.exitCode() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
#endif

#pragma endregion

GenshinTianLiBattleClient::GenshinTianLiBattleClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
#ifdef USE_QT_NET
	manager = new QNetworkAccessManager(this);
#endif

	/// QLabel* label = new QLabel(this);
	/// label->setGeometry(0, 0, this->width(), this->height());
	/// label->setText("wait api");
	/// 
	/// QString check_version = GetVersion();
	/// int new_version_major = check_version.split(".")[0].toInt();
	/// int new_version_minor = check_version.split(".")[1].toInt();
	/// int new_version_patch = check_version.split(".")[2].toInt();
	/// if(new_version_major > tl::bettle::version::version_major || new_version_minor > tl::bettle::version::version_minor || new_version_patch > tl::bettle::version::version_patch)
	/// {
	/// 	label->setText(check_version);
	/// 	QString download_link = GetDownloadLink();
	/// 	label->setText(download_link);
	/// 	UpdateSelf(download_link);
	/// }
	/// else
	/// {
	/// 	label->setText("no new version");
	/// }

}

GenshinTianLiBattleClient::~GenshinTianLiBattleClient()
{
#ifdef USE_QT_NET
	manager->deleteLater();
	manager = nullptr;
#endif
}
void GenshinTianLiBattleClient::UpdateSelf(QString &updata_pkg_url)
{
	///  // 0 弹窗提示下载
	///  QDialog* dialog = new QDialog(this);
	///  //dialog.setWindowFlags(Qt::FramelessWindowHint);
	///  dialog->setFixedSize(400, 200);
	///  QLabel* label = new QLabel(dialog);
	///  label->setGeometry(0, 0, dialog->width(), dialog->height());
	///  label->setText("Downloading...");
	///  dialog->show();
	///  
	///  // 下载改用curl
	///  GetDownloadFile(updata_pkg_url, "GenshinTianLiBattleClient_update.zip");
	///  
	///  qDebug() << QDir::currentPath();
	///  
	///  QString release_path = "new_version/";
	///  QString release_exe = QDir::currentPath() + "/" + release_path + "GenshinTianLiBattleClient.exe";
	///  
	///  QZipReader reader("GenshinTianLiBattleClient_update.zip");
	///  auto list = reader.fileInfoList();
	///  if (list.isEmpty())
	///  {
	///  	label->setText("list.isEmpty()");
	///  	qDebug() << "Updata Faile";
	///  	return;
	///  }
	///  else
	///  {
	///  	QString s = "";
	///  	for (auto& f : list)
	///  	{
	///  		s += f.filePath;
	///  	}
	///  
	///  	label->setText("list " + s);
	///  	qDebug() << "list " + s;
	///  
	///  	QDir dir;
	///  	if (!dir.exists(release_path))
	///  	{
	///  		dir.mkpath(release_path);
	///  	}
	///  	reader.extractAll(release_path);
	///  	qDebug() << "release_exe : " << release_exe;
	///  	// release_exe 是否存在
	///  	if (QFile::exists(release_exe))
	///  	{
	///  		label->setText("release_exe exists");
	///  		qDebug() << "release_exe exists";
	///  		QFile::rename(release_exe, release_exe + ".new");
	///  
	///  	}
	///  	else
	///  	{
	///  		label->setText("release_exe not exists");
	///  		qDebug() << "release_exe not exists";
	///  	}
	///  }
	///  reader.close();
	///  QFile::remove("GenshinTianLiBattleClient_update.zip");
	///  
	///  // 将自身重命名为old
	///  QString app_exe = "GenshinTianLiBattleClient.exe";
	///  QString app_path = QCoreApplication::applicationFilePath().replace(app_exe, "");
	///  QString app_exe_path = QCoreApplication::applicationFilePath();
	///  QString old_exe_path = app_exe_path + ".old";
	///  QFile::rename(app_exe_path, old_exe_path);
	///  qDebug() << "rename " << app_exe_path << " to " << old_exe_path;
	///  
	///  // 将release_exe拷贝到当前目录
	///  bool copy_res= QFile::copy(release_exe, app_exe_path);
	///  qDebug() << "copy " << release_exe << " to " << app_path << " res " << copy_res;
	///  
	///  
	///  // 移除 old
	///  QFile::remove(release_exe + ".new");
	///  if (release_path.isEmpty())
	///  {
	///  	QDir dir;
	///  	dir.rmdir(release_path);
	///  }
	///  QFile::remove(old_exe_path);
	///  
	///  
	///  
	///  // 替换自身
	///  QProcess::startDetached(app_exe_path);
	///  qDebug() << "startDetached " << app_exe_path;
	///  
	///  
	///  exit(1);
	
}
