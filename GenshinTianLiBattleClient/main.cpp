#include "GenshinTianLiBattleClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{	
	// -v 输出版本号
	if (argc > 1 && strcmp(argv[1], "-v") == 0)
	{
		printf("%s\n", tl::battle::client::version::version);
		return 0;
	}
	// -V 输出完整编译号 
	if (argc > 1 && strcmp(argv[1], "-V") == 0)
	{
		printf("%s\n", tl::battle::client::version::build_version);
		return 0;
	}

    QApplication a(argc, argv);
    GenshinTianLiBattleClient w;
    w.show();
    return a.exec();
}
