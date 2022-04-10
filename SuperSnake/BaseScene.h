#ifndef BASESCENE_H
#define BASESCENE_H

#include <QMainWindow>
#include <QApplication>

class BaseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit BaseScene(QWidget *parent = nullptr,int w = 800,int h = 600);
protected:
    void closeEvent(QCloseEvent *event);  //窗口關閉事件
protected:
    int width;  //場景的寛
    int height; //場景高

signals:

};

#endif // BASESCENE_H
