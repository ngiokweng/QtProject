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
    void createBtn(QPushButton*& btn,QSize btnSize,QFont btnFont,int loc_y,int offset); //創建菜單界面的按鈕
    void enterLoginScene(); //進入【登錄界面】
    void enterSettingScene(); //進入【設置界面】


private:
    Ui::MenuScene *ui;
    int width;
    int height;

};
#endif // MENUSCENE_H
