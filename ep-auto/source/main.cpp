#include <QCoreApplication>
#include "menu.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    FILE *in=0, *refbook=0;
    struct autoshow *pautoshow=0, *pendautoshow=0;
    struct refbook *pmade=0, *pmodel=0, *pclass=0;
    MainMenu(pmade, pmodel, pclass, pautoshow, pendautoshow, in, refbook);
    exit(0);
    return a.exec();
}
