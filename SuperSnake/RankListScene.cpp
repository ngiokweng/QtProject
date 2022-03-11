#include "RankListScene.h"
#include <QTabWidget>
#include <QPushButton>
#include <QTabBar>
#include <QDebug>
#include <QTableWidget>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <data.h>
#include <algorithm>

RankListScene::RankListScene(QWidget *parent,int width,int height) : QMainWindow(parent),width(width),height(height)
{
    getRankInfo();
    init();
}

//獲取所有排行榜信息
/*
【rankInfo的說明如下】：
rankInfo[speed][i].first：代表speed速度排行榜中，第i條記錄的分數
rankInfo[speed][i].second.first：代表speed速度排行榜中，第i條記錄，的用戶名
rankInfo[speed][i].second.second：代表speed速度排行榜中，第i條記錄，的創建時間
*/
void RankListScene::getRankInfo(){
    //文件讀入操作
    QFile rankListFile;
    rankListFile.setFileName(rankListPath);
    rankListFile.open(QIODevice::ReadOnly);
    QByteArray rankData = rankListFile.readAll();

    QJsonDocument jsonDoc = QJsonDocument::fromJson(rankData);
    QJsonObject jsonObj = jsonDoc.object();

    //按rankInfo的儲存格式讀入所有排行榜的資料
    for(auto& speed:jsonObj.keys()){
        QJsonObject speedObj = jsonObj[speed].toObject();
        for(auto& userId:speedObj.keys()){
            QJsonObject userObj = speedObj[userId].toObject();
            rankInfo[speed.toInt()].emplace_back(qMakePair(userObj["maxScore"].toInt(),
                                                 qMakePair(userObj["userName"].toString(),userObj["date"].toString())));

        }
    }
    rankListFile.close();

    //分別對不同速度的排行榜，按分數由高到低排序
    for(auto& ele:rankInfo){
        sort(ele.second.begin(),ele.second.end(),[=](QPair<int,QPair<QString,QString>>& a1,QPair<int,QPair<QString,QString>>& a2){
            return a1.first>a2.first;
        });
    }


}

//初始化當前場景
void RankListScene::init(){
    this->setFixedSize(width,height);
    this->setWindowTitle("【SuperSnake】排行榜");

    //創建標籤頁容器
    QTabWidget* tabWidget = new QTabWidget(this);
    //設置tabBar的字體
    tabWidget->tabBar()->setFont(QFont("Adobe 繁黑體 Std B",16));
    tabWidget->tabBar()->adjustSize();
    tabWidget->setFixedSize(this->size());
    tabWidget->show();

    int tabBarHeight = tabWidget->tabBar()->height();

    //用來儲存10個標籤頁(對應10個不同速度的排行榜)
    QWidget* tabItems[10];
    //用來儲存10個排行榜的展示用的表格
    QTableWidget* tabels[10];


    /* 初始化並設置所有速度的排行榜 */
    for(int i = 0;i<10;i++){
        int recordNum = rankInfo[i+1].size(); //【速度i+1排行榜】的記錄數

        /* 標籤頁的設置 */
        tabItems[i] = new QWidget(this);
        tabItems[i]->setFixedSize(this->width,this->height-tabBarHeight); //設置所有標籤頁的大小

        /* 表格的設置 */
        tabels[i] = new QTableWidget(tabItems[i]);
        tabels[i]->setFixedSize(tabItems[i]->size()); //當前表格大小為所在標籤頁的大小
        tabels[i]->setColumnCount(3); //列數為3
        tabels[i]->setRowCount(recordNum); //根據當前速度的排行榜來設置行數
        tabels[i]->horizontalHeader()->setDefaultSectionSize(width/3); //設置列寬，這裡平均為3份，同等大小
        tabels[i]->setHorizontalHeaderLabels(QStringList()<<"用戶名"<<"最高分數"<<"創建時間"); //設置表頭元素
        tabels[i]->setEditTriggers(QAbstractItemView::NoEditTriggers); //將表格設為"只讀"

        //構造行
        for(int k = 0;k < recordNum;k++){
            int j=0;
            QTableWidgetItem* score = new QTableWidgetItem(QString::number(rankInfo[i+1][k].first));
            QTableWidgetItem* userName = new QTableWidgetItem(rankInfo[i+1][k].second.first);
            QTableWidgetItem* date = new QTableWidgetItem(rankInfo[i+1][k].second.second);
            score->setTextAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);
            score->setFont(QFont("Adobe 楷体 Std R",14));
            userName->setTextAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);
            userName->setFont(QFont("Adobe 楷体 Std R",14));
            date->setTextAlignment(Qt::AlignHCenter |  Qt::AlignVCenter);
            date->setFont(QFont("Adobe 楷体 Std R",14));

            //k代表行，j代表列
            tabels[i]->setItem(k,j,userName);
            tabels[i]->setItem(k,++j,score);
            tabels[i]->setItem(k,++j,date);
        }

        tabWidget->addTab(tabItems[i],QString("%1倍速").arg(i+1));
    }

    //返回的按鈕
    QPushButton* backBtn = new QPushButton("返回",this);
    backBtn->setFont(QFont("Adobe 楷体 Std R",14));
    backBtn->adjustSize();
    backBtn->move(width-backBtn->width(),0);
    connect(backBtn,&QPushButton::clicked,[this](){
        this->close();
        //發送返回【設定界面】的信號
        emit backToMenuScene();


    });

}
