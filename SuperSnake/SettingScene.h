#ifndef SETTINGSCENE_H
#define SETTINGSCENE_H

#include <QMainWindow>
#include <QLineEdit>
#include "MapScene.h"
#include "Snake.h"
#include <QComboBox>

class SettingScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingScene(QWidget *parent = nullptr,int width = 600,int height = 480);
    ~SettingScene();
    void init(); //初始化【設置】界面
    void enterMapScene(); //進入MapScene
    void onSizeSelectChange();

signals:
    void backToMenuScene();

private:
    int width;  //【設置界面】的寬
    int height; //【設置界面】的高
    Snake* snake = nullptr;
    QComboBox* colSelect; //地圖[列數]選擇框
    QComboBox* rowSelect; //地圖[行數]選擇框
    QComboBox* snakeSizeSelect; //[蛇大小]選擇框
    QComboBox* speedSelect;  //[蛇速度]選擇框


};

#endif // SETTINGSCENE_H
