#include "SettingScene.h"
#include <QPushButton>
#include "Snake.h"

SettingScene::SettingScene(QWidget *parent,int width,int height) : QMainWindow(parent),width(width),height(height)
{
    init();
}

void SettingScene::enterMapScene(){
    Snake* snake = new Snake(3,20);
    MapScene* mapScence = new MapScene(this,25,40,snake);
    this->hide();
    mapScence->show();
}

//初始化【設置】界面
void SettingScene::init(){
    this->setFixedSize(width,height);
    this->setWindowTitle("【SuperSnake】遊戲設置");

    rowInput = new QLineEdit(this);
    rowInput->setPlaceholderText("在此輸入地圖的行數[10~50]");
    rowInput->move(50,50);
    rowInput->adjustSize();

    colInput = new QLineEdit(this);
    colInput->setPlaceholderText("在此輸入地圖的列數[10~25]");
    colInput->move(50,200);
    colInput->adjustSize();

    //確定進入【MapScene】的button
    QPushButton* enter = new QPushButton("點擊進入",this);
    enter->move(100,300);
    connect(enter,&QPushButton::clicked,this,&SettingScene::enterMapScene);



}
