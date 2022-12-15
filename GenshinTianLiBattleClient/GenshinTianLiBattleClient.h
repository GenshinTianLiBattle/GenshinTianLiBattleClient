#pragma once
#include <QtWidgets/QWidget>
#include "ui_GenshinTianLiBattleClient.h"

#include "CoreManager.h"
#include "common/TPopup.h"
#include "def/version/Version.h" // This is the header file that contains the version number

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
private:
    QPoint move_press;
    QPoint move_value;
    bool is_left_clicked = false;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
public slots:
    void UpdateSelf(QString& updata_pkg_url);
    void show_frame(QImage img);
    void find_genshin(bool is_exist);
    void timer_tick();
};
