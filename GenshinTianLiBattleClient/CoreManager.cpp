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
	
	tick_timer->setInterval(42);
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

#include <QtWin> 

void CoreManager::OnTick()
{
	//static cv::VideoWriter writer("save.mp4", 0, 30, cv::Size(1920, 1080));
	//static cv::VideoWriter writer_alpha("save_alpha.mp4", 0, 30, cv::Size(1920, 1080));
	tick_auto tc;
	qDebug() << "tick:" << tc;

	if (genshin_handle == nullptr)
	{
		genshin_handle = FindWindowA("UnityWndClass", "原神");
		//return;
	}
	if (!IsWindow(genshin_handle))
	{
		if (genshin_is_exist)
		{
			genshin_is_exist = false;
			emit genshin_exist_changed(genshin_is_exist);
		}
		return;
	}
	if (!genshin_is_exist)
	{
		genshin_is_exist = true;
		emit genshin_exist_changed(genshin_is_exist);
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
	BITMAP bmp{};
	GetObject(hCaptureBitmap, sizeof(BITMAP), &bmp);
	auto map = QtWin::fromHBITMAP(hCaptureBitmap, QtWin::HBitmapAlpha);
	cv::Mat mat;
	mat.create(bmp.bmHeight, bmp.bmWidth, CV_8UC4);
	GetBitmapBits(hCaptureBitmap, bmp.bmWidthBytes * bmp.bmHeight, mat.data);
	DeleteObject(hCaptureBitmap);
	DeleteDC(hCaptureDC);
	ReleaseDC(genshin_handle, hWindowDC);
	std::vector<cv::Mat> split;
	cv::split(mat, split);

	//writer << mat;
	//writer_alpha << split[3];
	cv::resize(mat, mat, cv::Size(800, 450));

	QImage image((const uchar*)(mat.data), mat.cols, mat.rows, mat.cols * (mat.channels()), QImage::Format_ARGB32);
	
	emit next_frame(image);
}

QString CoreManager::get_token()
{
	auto token =api::login("user", "user");
	if (token != nullptr)
	{
		qDebug() << "token: " << token;
		//core->free_str(token);
	}
	return QString(token);
}

void CoreManager::OnTick_2nd()
{
	tick_auto tc;
	qDebug() << "tick:" << tc;

	if (genshin_handle == nullptr)
	{
		genshin_handle = FindWindowA("UnityWndClass", "原神");
		//return;
	}
	if (!IsWindow(genshin_handle))
	{
		if (genshin_is_exist)
		{
			genshin_is_exist = false;
			emit genshin_exist_changed(genshin_is_exist);
		}
		return;
	}
	if (!genshin_is_exist)
	{
		genshin_is_exist = true;
		emit genshin_exist_changed(genshin_is_exist);
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
	
	auto map = QtWin::fromHBITMAP(hCaptureBitmap, QtWin::HBitmapAlpha);
	DeleteObject(hCaptureBitmap);
	DeleteDC(hCaptureDC);
	ReleaseDC(genshin_handle, hWindowDC);
	
	map = map.scaled(800, 450);

	QImage image = map.toImage();
	emit next_frame(image);
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
