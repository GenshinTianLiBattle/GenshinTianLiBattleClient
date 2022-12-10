#include "GenshinTianLiBattleClient.h"

#include "def/version/Version.h" // This is the header file that contains the version number

#include <QString>
#include <QPixmap>
#include <QTimer>

GenshinTianLiBattleClient::GenshinTianLiBattleClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

	popup = new TPopup();
	

	ui.textEdit->setText(core_manager.get_token());


	connect(&core_manager, &CoreManager::next_frame, this, &GenshinTianLiBattleClient::show_frame);
	connect(&core_manager, &CoreManager::genshin_exist_changed, this, &GenshinTianLiBattleClient::find_genshin);
	
	timer = new QTimer(this);
	timer->setInterval(100);
	connect(timer, &QTimer::timeout, this, &GenshinTianLiBattleClient::timer_tick);
	connect(ui.pushButton, &QPushButton::clicked, [&]() {
		static bool is_clicked = false;
		if (is_clicked)
		{
			is_clicked = false;
			timer->stop();
			popup->hide();
		}
		else 
		{
			is_clicked = true;
			timer->start();
			popup->show();
		}
		});
}

GenshinTianLiBattleClient::~GenshinTianLiBattleClient()
{
	delete popup;
}
void GenshinTianLiBattleClient::show_frame(QImage img)
{
	QPixmap map = QPixmap::fromImage(img);
	ui.label->setPixmap(map);
	
}
void GenshinTianLiBattleClient::find_genshin(bool is_exist)
{
	if (is_exist)
	{
		ui.pushButton->setText("genshin exist");
		
	}
	else
	{
		ui.pushButton->setText("genshin not exist");
	}
}
void GenshinTianLiBattleClient::timer_tick()
{
	// 获取鼠标位置
	POINT point;
	GetCursorPos(&point);
	// 获取鼠标所在窗口句柄
	HWND hwnd = WindowFromPoint(point);
	// 获取窗口标题
	char title[256];
	GetWindowTextA(hwnd, title, 256);

	QString str;
	str = "x: " + QString::number(point.x) + " y: " + QString::number(point.y) + " | " + title;
	
	ui.textEdit->setText(str);
}
void GenshinTianLiBattleClient::UpdateSelf(QString &updata_pkg_url)
{
}
