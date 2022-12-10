#include "TPopup.h"
#include <QMouseEvent>

#include <windows.h>

TPopup::TPopup(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setAttribute(Qt::WA_TranslucentBackground, true);

	//this->setAttribute(Qt::WA_TransparentForMouseEvents);
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow | Qt::WindowStaysOnTopHint);

	//SetWindowLong((HWND)winId(), GWL_EXSTYLE, GetWindowLong((HWND)winId(), GWL_EXSTYLE) |WS_EX_TRANSPARENT | WS_EX_LAYERED);
}

TPopup::~TPopup()
{}

void TPopup::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton )
	{
		
		move_press = event->globalPos();
			is_left_clicked = true;
		
	}
	//event->ignore();
}
void TPopup::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton) {
		is_left_clicked = false;
	}
	//event->ignore();
}
void TPopup::mouseMoveEvent(QMouseEvent* event)
{
	if (is_left_clicked) {
		move_value = event->globalPos();
		this->move(this->pos() + move_value - move_press);
		move_press = move_value;
	}
	//event->ignore();
}
