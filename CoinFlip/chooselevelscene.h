#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include "playscene.h"

class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);

    PlayScene* pScene = NULL;

signals:
    //自定義返回信號
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
