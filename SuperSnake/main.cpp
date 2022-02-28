#include "menuscene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuScene w;
    w.show();
    return a.exec();
}
