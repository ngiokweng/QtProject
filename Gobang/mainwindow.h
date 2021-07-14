#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "GameModel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameModel* game = NULL; //遊戲指針
    GameType game_type = AI;  //儲存遊戲類型
    int clickPosRow,clickPosCol; //存儲點擊的位置
    bool selectPos;  //是否移動到合適的位置，以選中摸個交叉點

    void paintEvent(QPaintEvent* event);
    void initGame(); //初始化遊戲
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void chessOneByPerson();
private slots:
    void chessOneByAI();
};
#endif // MAINWINDOW_H
