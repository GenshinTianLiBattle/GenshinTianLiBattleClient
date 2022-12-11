#pragma once
#include <QObject>
#include <QImage>

namespace tl::battle::core {
	class TianLiBattleCore;
}

#include <Windows.h>

class CoreManager  : public QObject
{
	Q_OBJECT

public:
	CoreManager(QObject *parent = NULL);
	~CoreManager();
	
private:
	HWND genshin_handle = 0;
	bool genshin_is_exist = false;
private:
	QTimer* tick_timer;
private:
	tl::battle::core::TianLiBattleCore* core = nullptr;
public:
	QString get_token();
public slots:
	void OnTick();
	void OnTick_2nd();
	void set_genshin_handle(HWND handle);
	void checkVersionServer();
	void update_app();
signals:
	void next_frame(QImage img);
	void genshin_exist_changed(bool is_exist);
};
