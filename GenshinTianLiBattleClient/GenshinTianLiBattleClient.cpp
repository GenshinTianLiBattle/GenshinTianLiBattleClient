#include "GenshinTianLiBattleClient.h"

#include "def/version/Version.h" // This is the header file that contains the version number

#include <QPixmap>

GenshinTianLiBattleClient::GenshinTianLiBattleClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
	
	ui.textEdit->setText(core_manager.get_token());


	connect(&core_manager, &CoreManager::next_frame, this, &GenshinTianLiBattleClient::show_frame);
	
    
}

GenshinTianLiBattleClient::~GenshinTianLiBattleClient()
{
}
void GenshinTianLiBattleClient::show_frame(QImage img)
{
	QPixmap map = QPixmap::fromImage(img);
	ui.label->setPixmap(map);
	
}
void GenshinTianLiBattleClient::UpdateSelf(QString &updata_pkg_url)
{
}
