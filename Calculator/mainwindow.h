#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "value.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //儲存所有輸入的值和運算符
    QVector<Value> allValueAndOperator;
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
