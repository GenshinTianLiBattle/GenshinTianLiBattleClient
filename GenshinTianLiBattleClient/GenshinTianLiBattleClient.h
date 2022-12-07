#pragma once
#include <QNetworkAccessManager>
#include <QtWidgets/QWidget>
#include "ui_GenshinTianLiBattleClient.h"

//#define USE_QT_NET

class GenshinTianLiBattleClient : public QWidget
{
    Q_OBJECT

public:
    GenshinTianLiBattleClient(QWidget *parent = nullptr);
    ~GenshinTianLiBattleClient();

private:
    Ui::GenshinTianLiBattleClientClass ui;
private:
#ifdef USE_QT_NET
    QNetworkAccessManager* manager = nullptr;
#endif 
private:
    QString GetVersion();
    QString GetDownloadLink();
    bool GetDownloadFile(QString url, QString path);
public slots:
    void UpdateSelf(QString& updata_pkg_url);
};
