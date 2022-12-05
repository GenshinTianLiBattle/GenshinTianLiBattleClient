#pragma once
#include <QNetworkAccessManager>
#include <QtWidgets/QWidget>
#include "ui_GenshinTianLiBattleClient.h"

class GenshinTianLiBattleClient : public QWidget
{
    Q_OBJECT

public:
    GenshinTianLiBattleClient(QWidget *parent = nullptr);
    ~GenshinTianLiBattleClient();

private:
    Ui::GenshinTianLiBattleClientClass ui;
private:
    QNetworkAccessManager* manager = nullptr;
private:
    QString GetVersion();
    QString GetDownloadLink();
    bool GetDownloadFile(QString url, QString path);
public slots:
    void UpdateSelf(QString& updata_pkg_url);
};
