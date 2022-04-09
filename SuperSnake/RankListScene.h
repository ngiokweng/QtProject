#ifndef RANKLISTSCENE_H
#define RANKLISTSCENE_H

#include "BaseScene.h"
#include <map>
#include <vector>
#include <QString>
#include <QPair>

using std::map;
using std::vector;
using std::pair;

class RankListScene : public BaseScene
{
    Q_OBJECT
public:
    explicit RankListScene(QWidget *parent = nullptr,int width = 600,int height = 480);
    void init(); //初始化當前場景
    void getRankInfo();  //獲取所有排行榜信息

signals:
    void backToMenuScene();

private:
    map<int,vector<QPair<int,QPair<QString,QString>>>> rankInfo; //rankInfo[speed][i].first：代表speed速度排行榜中，第i條記錄的分數
                                                                 //rankInfo[speed][i].second.first：代表speed速度排行榜中，第i條記錄，的用戶名
                                                                //rankInfo[speed][i].second.second：代表speed速度排行榜中，第i條記錄，的創建時間
};

#endif // RANKLISTSCENE_H
