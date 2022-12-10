#pragma once
#include <QtWidgets/QWidget>
#include "ui_GenshinTianLiBattleClient.h"

#include "CoreManager.h"
#include "common/TPopup.h"

class GenshinTianLiBattleClient : public QWidget
{
    Q_OBJECT

public:
    GenshinTianLiBattleClient(QWidget *parent = nullptr);
    ~GenshinTianLiBattleClient();

private:
    Ui::GenshinTianLiBattleClientClass ui;
private:
    QTimer* timer = nullptr;
private:
	CoreManager core_manager;
private:
	TPopup* popup = nullptr;

public slots:
    void UpdateSelf(QString& updata_pkg_url);
    void show_frame(QImage img);
    void find_genshin(bool is_exist);
    void timer_tick();
};
