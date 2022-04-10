#include "BaseScene.h"
#include <QMessageBox>
#include <QCloseEvent>

BaseScene::BaseScene(QWidget *parent,int w,int h) : QMainWindow(parent),width(w),height(h)
{

}

void BaseScene::closeEvent(QCloseEvent *event){
    //若不做以下處理，程序的進程可能不會完全關閉
    if(event->spontaneous()){  //判斷是否用戶點擊[X]，是則為True
        if(QMessageBox::question(this,"提示","確定要退出整個程序？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No) == QMessageBox::Yes){
            qApp->quit(); //退出整個程序
        }else{
            event->ignore();  //忽視退出的操作
        }
    }else{
        event->accept();
    }
}
