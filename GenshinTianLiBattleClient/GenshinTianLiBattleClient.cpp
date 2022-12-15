#include "GenshinTianLiBattleClient.h"

#include <QMouseEvent>
#include <QString>
#include <QPixmap>
#include <QTimer>

GenshinTianLiBattleClient::GenshinTianLiBattleClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);

	popup = new TPopup();
	popup->show();


	//ui.textEdit->setText(core_manager.get_token());

	connect(ui.pushButton_2, &QPushButton::clicked,&core_manager,&CoreManager::update_app);

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

void GenshinTianLiBattleClient::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		// ui.TitleBar
		if (ui.TitleBar->geometry().contains(event->pos()))
		{
			move_press = event->globalPos();
			move_value = this->pos();
			is_left_clicked = true;
		}
	}
	//event->ignore();
}
void GenshinTianLiBattleClient::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		is_left_clicked = false;
	}
	//event->ignore();
}
void GenshinTianLiBattleClient::mouseMoveEvent(QMouseEvent* event)
{
	if (is_left_clicked) {
		move_value = event->globalPos();
		this->move(this->pos() + move_value - move_press);
		move_press = move_value;
	}
	//event->ignore();
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
	// ��ȡ���λ��
	POINT point;
	GetCursorPos(&point);
	// ��ȡ������ڴ��ھ��
	HWND hwnd = WindowFromPoint(point);
	// ��ȡ���ڱ���
	char title[256];
	GetWindowTextA(hwnd, title, 256);

	QString str;
	str = "x: " + QString::number(point.x) + " y: " + QString::number(point.y) + " | " + title;
	
	//ui.textEdit->setText(str);
}
void GenshinTianLiBattleClient::UpdateSelf(QString &updata_pkg_url)
{
}
