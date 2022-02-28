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
    void initMenu(int width,int height); //初始化菜單選項
    void createBtn(QPushButton*& btn,QSize btnSize,QFont btnFont,int loc_y,int offset); //創建菜單界面的按鈕

private:
    Ui::MenuScene *ui;
    int width;
    int hegith;
};
#endif // MENUSCENE_H
