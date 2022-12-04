#include "GenshinTianLiBattleClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GenshinTianLiBattleClient w;
    w.show();
    return a.exec();
}
