#pragma once

#include <QWidget>
#include "ui_TPopup.h"

class TPopup : public QWidget
{
	Q_OBJECT

public:
	TPopup(QWidget *parent = nullptr);
	~TPopup();
private:
    QPoint move_press;
    QPoint move_value;
    bool is_left_clicked = false;
    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    //void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
private:
	Ui::TPopupClass ui;
};
