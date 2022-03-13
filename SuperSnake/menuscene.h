#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <QWidget>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MenuScene; }
QT_END_NAMESPACE

//菜單場景class
class MenuScene : public QWidget
{
    Q_OBJECT

public:

    MenuScene(QWidget *parent = nullptr);
    ~MenuScene();
    void initMenu(); //初始化菜單選項
    void createBtn(QPushButton*& btn,QSize btnSize,int loc_y,int offset); //創建菜單界面的按鈕
    void enterLoginScene(); //進入【登錄界面】

public slots:
    void enterSettingScene(); //進入【設置界面】
    void enterRankListScene(); // 進入【排行榜界面】
    void logout(); //登出
    void showSelfInfo(); //顯示個人信息


private:
    Ui::MenuScene *ui;
    int width;
    int height;

};
#endif // MENUSCENE_H
