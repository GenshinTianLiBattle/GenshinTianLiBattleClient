#include "GenshinTianLiBattleClient.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{	
	// -v Êä³ö°æ±¾ºÅ
	if (argc > 1 && strcmp(argv[1], "-v") == 0)
	{
		printf("%s\n", tl::battle::client::version::version);
		return 0;
	}

    QApplication a(argc, argv);
    GenshinTianLiBattleClient w;
    w.show();
    return a.exec();
}
