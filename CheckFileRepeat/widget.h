#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QThread>
#include "FileMd5.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void closeEvent(QCloseEvent* event);

    FileMd5 md5;
    QHash<QByteArray, QStringList> dumplates;
    bool isDone = true; //判斷窗口可否關閉
signals:
    void checkDumplate(const QString &path);

private slots:
    void on_pushButton_clicked();
    void onGotDumplate(const QHash<QByteArray,QStringList> &dumplates);
    void onProcess(int current, int total);

    void on_listWidget_currentTextChanged(const QString &currentText);

private:
    Ui::Widget *ui;
    QThread thread;
};
#endif // WIDGET_H
