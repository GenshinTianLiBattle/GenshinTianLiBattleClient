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
private:
	QTimer* tick_timer;
private:
	tl::battle::core::TianLiBattleCore* core = nullptr;
public slots:
	void OnTick();
	void set_genshin_handle(HWND handle);
	void checkVersionServer();
signals:
	void next_frame(QImage img);
};
