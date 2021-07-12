#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString butImg);
    void changeFlag();
    void mousePressEvent(QMouseEvent* event);

    int posX;
    int posY;
    bool coinFlag; //1正 0反
    QTimer* timer1 = NULL; //正->反
    QTimer* timer2 = NULL; //反->正
    int min = 1;
    int max = 8;
    bool isAnimation = false;
    bool isWin = false;

signals:

};

#endif // MYCOIN_H
