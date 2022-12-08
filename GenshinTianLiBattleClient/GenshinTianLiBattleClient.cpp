#include "GenshinTianLiBattleClient.h"

#include "def/api/Api.h" // This is the header file that contains the URL
#include "def/version/Version.h" // This is the header file that contains the version number

GenshinTianLiBattleClient::GenshinTianLiBattleClient(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

}

GenshinTianLiBattleClient::~GenshinTianLiBattleClient()
{
}
void GenshinTianLiBattleClient::UpdateSelf(QString &updata_pkg_url)
{
}
