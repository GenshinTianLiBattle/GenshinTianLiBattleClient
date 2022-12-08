#include "CoreManager.h"

#define GenshinTianLiBattleCore_Dll
#ifdef GenshinTianLiBattleCore_Dll
#include "../GenshinTianLiBattleClient.Core/TianLiBattle.Core.h"
#pragma comment(lib, "GenshinTianLiBattleClient.Core.lib")
using namespace tl::battle;
#endif // GenshinTianLiBattleCore_Dll

#include <QTimer>
#include <QImage>
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
		genshin_handle = FindWindowA("UnityWndClass", "Ô­Éñ");
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

	cv::cvtColor(mat, mat, cv::COLOR_RGBA2RGB);

	QImage image((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols * (mat.channels()), QImage::Format_RGB32);
	//QImage image((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols * (mat.channels()), QImage::Format_ARGB32);

	emit next_frame(image);
}

QString CoreManager::get_token()
{
	auto token = core->login("user", "user");
	if (token != nullptr)
	{
		qDebug() << "token: " << token;
		//core->free_str(token);
	}
	return QString(token);
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
