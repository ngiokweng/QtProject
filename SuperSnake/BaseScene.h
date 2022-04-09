#ifndef BASESCENE_H
#define BASESCENE_H

#include <QMainWindow>

class BaseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit BaseScene(QWidget *parent = nullptr,int w = 800,int h = 600);
protected:
    int width;  //場景的寛
    int height; //場景高

signals:

};

#endif // BASESCENE_H
