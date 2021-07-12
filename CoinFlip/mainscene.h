#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    void paintEvent(QPaintEvent* event);

    ChooseLevelScene* chooseLevelScene = NULL;
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
