#include "menuscene.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuScene w;
//    w.show(); //先不要顯示主窗口，登錄後才顯示
    return a.exec();
}
