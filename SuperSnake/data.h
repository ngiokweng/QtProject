#ifndef DATA_H
#define DATA_H
#include <QSize>
#include <QString>

const QSize maxMapSize(1600,900); //地圖寬、高的上限(<=)
const QSize minMapSize(600,480);  //地圖寬、高的下限(>=)
const int maxSnakeSize = 40; //蛇大小的上限
const int minSnakeSize = 5; //蛇大小的下限
const QString accountPath = "./data/user_account.json"; //儲存用戶帳號信息的檔案的相對路徑


#endif // DATA_H
