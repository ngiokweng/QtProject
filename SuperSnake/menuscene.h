#ifndef MENUSCENE_H
#define MENUSCENE_H

#include "BaseScene.h"
#include <QPushButton>


//菜單場景class
class MenuScene : public BaseScene
{
    Q_OBJECT

public:

    MenuScene(QWidget *parent = nullptr,int w = 800,int h = 600);
    ~MenuScene();
    void initMenu(); //初始化菜單選項
    void setBtn(QPushButton*& btn,QSize btnSize,int loc_y,int offset); //設置按鈕的基本樣式及位置
    void enterLoginScene(); //進入【登錄界面】

public slots:
    void enterSettingScene(); //進入【設置界面】
    void enterRankListScene(); // 進入【排行榜界面】
    void logout(); //登出
    void showSelfInfo(); //顯示個人信息

};
#endif // MENUSCENE_H
