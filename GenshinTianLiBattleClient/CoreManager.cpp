#include "CoreManager.h"

#define GenshinTianLiBattleCore_Dll
#ifdef GenshinTianLiBattleCore_Dll
#include "../GenshinTianLiBattleClient.Core/TianLiBattle.Core.h"
#pragma comment(lib, "GenshinTianLiBattleClient.Core.lib")
using namespace tl::battle;
#endif // GenshinTianLiBattleCore_Dll

#include <QTimer>
#include <qDebug>

#include <opencv2/opencv.hpp>

CoreManager::CoreManager(QObject *parent)
	: QObject(parent)
{
#ifdef GenshinTianLiBattleCore_Dll
	core = core::TianLiBattleCore::GetInstance();
#endif // GenshinTianLiBattleCore_Dll

	tick_timer = new QTimer(this);
	
	tick_timer->setInterval(1000);
	tick_timer->start();
	connect(tick_timer, &QTimer::timeout, this, &CoreManager::OnTick);
	checkVersionServer();
}

CoreManager::~CoreManager()
{
	if (core != nullptr)
	{
		delete core;
	}
}

class tick_auto
{
public:
	tick_auto() {
		tick_auto::tick_count++;
	}
	~tick_auto() {}
	static int tick_count;
	operator int()
	{
		return tick_count;
	}
};
int tick_auto::tick_count=0;

void CoreManager::OnTick()
{
	tick_auto tc;
	qDebug() << "tick:" << tc;

	if (genshin_handle == nullptr)
	{
		return;
	}

	RECT rect;
	GetWindowRect(genshin_handle, &rect);
	int width = rect.right - rect.left;
	int height = rect.bottom - rect.top;
	HDC hWindowDC = GetDC(genshin_handle);
	HDC hCaptureDC = CreateCompatibleDC(hWindowDC);
	HBITMAP hCaptureBitmap = CreateCompatibleBitmap(hWindowDC, width, height);
	SelectObject(hCaptureDC, hCaptureBitmap);
	BitBlt(hCaptureDC, 0, 0, width, height, hWindowDC, 0, 0, SRCCOPY | CAPTUREBLT);
	BITMAP bmp;
	GetObject(hCaptureBitmap, sizeof(BITMAP), &bmp);
	cv::Mat mat;
	mat.create(bmp.bmHeight, bmp.bmWidth, CV_8UC4);
	GetBitmapBits(hCaptureBitmap, bmp.bmWidthBytes * bmp.bmHeight, mat.data);
	DeleteObject(hCaptureBitmap);
	DeleteDC(hCaptureDC);
	ReleaseDC(genshin_handle, hWindowDC);

}

void CoreManager::set_genshin_handle(HWND handle)
{
	genshin_handle = handle;
}

void CoreManager::checkVersionServer()
{
	auto server_uesd = core->checkVersionServer();
	qDebug() << "server_uesd:" << server_uesd;
	
}
