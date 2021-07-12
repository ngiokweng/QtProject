#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include <QTimer>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int level);
    void paintEvent(QPaintEvent* event);

    int levelIndex;
    int gameArray[4][4];
    MyCoin* coinArray[4][4];
    bool isWin;

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
