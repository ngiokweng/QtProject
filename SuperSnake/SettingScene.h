#ifndef SETTINGSCENE_H
#define SETTINGSCENE_H

#include <QMainWindow>
#include <QLineEdit>
#include "MapScene.h"

class SettingScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingScene(QWidget *parent = nullptr,int width = 600,int height = 480);
    void init(); //初始化【設置】界面
    void enterMapScene();
private:
    int width;  //【設置界面】的寬
    int height; //【設置界面】的高
    QLineEdit* colInput;  //地圖【列數】的輸入框
    QLineEdit* rowInput;  //地圖【行數】的輸入框

};

#endif // SETTINGSCENE_H
