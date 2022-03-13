#ifndef DATA_H
#define DATA_H
#include <QSize>
#include <QString>

const QSize maxMapSize(1600,900); //地圖寬、高的上限(<=)
const QSize minMapSize(600,480);  //地圖寬、高的下限(>=)

const int maxSnakeSize = 40; //蛇大小的上限
const int minSnakeSize = 5; //蛇大小的下限

const QString accountPath = "./data/user_account.json";     //儲存用戶帳號信息的檔案的[相對路徑]
const QString currentUserPath = "./data/current_user.json";  //儲存當前登錄用戶信息的檔案的[相對路徑]
const QString rankListPath = "./data/rank_list.json";  //儲存當前登錄用戶信息的檔案的[相對路徑]

const QString jsonStorageUrl = "https://api.jsonstorage.net/v1/json/a0514254-5aa2-42ba-9191-8236d65a4dc6"; //網路JSON的請求Url


#endif // DATA_H
