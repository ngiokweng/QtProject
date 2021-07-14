#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <math.h>
#include <QMessageBox>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(
     MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE,
     MARGIN*2+BLOCK_SIZE*BOARD_GRAD_SIZE);
    initGame();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //設置抗鋸齒

    for(int i=0;i<BOARD_GRAD_SIZE+1;i++){
        //從左到右，第(i+1)條豎線
        painter.drawLine(MARGIN+BLOCK_SIZE*i,MARGIN,
                         MARGIN+BLOCK_SIZE*i,this->height()-MARGIN);
        //從上到下，第(i+1)條橫線
        painter.drawLine(MARGIN,MARGIN+BLOCK_SIZE*i,
                         this->width()-MARGIN,MARGIN+BLOCK_SIZE*i);
    }
    //繪製選中點
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    //繪製落子標記(防止鼠標出框越界)
    if(clickPosRow>0 && clickPosRow<BOARD_GRAD_SIZE &&
       clickPosCol>0 && clickPosCol<BOARD_GRAD_SIZE &&
        game->gameMapVec[clickPosRow][clickPosCol]==0){

        if(game->playerFlag){
            brush.setColor(Qt::black);
        }else{
            brush.setColor(Qt::white);
        }
        painter.setBrush(brush);
        painter.drawRect(MARGIN+BLOCK_SIZE*clickPosCol-MARK_SIZE/2,MARGIN+BLOCK_SIZE*clickPosRow-MARK_SIZE/2,MARK_SIZE,MARK_SIZE);
    }
    for(int i=0;i<BOARD_GRAD_SIZE;i++){
        for(int j=0;j<BOARD_GRAD_SIZE;j++){
            if(game->gameMapVec[i][j]==1){
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,CHESS_RADIUS*2,CHESS_RADIUS*2);
            }else if(game->gameMapVec[i][j]==-1){
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(MARGIN+BLOCK_SIZE*j-CHESS_RADIUS,MARGIN+BLOCK_SIZE*i-CHESS_RADIUS,CHESS_RADIUS*2,CHESS_RADIUS*2);
            }

        }
    }
    //判斷輸嬴
    if(clickPosCol>0 && clickPosCol<BOARD_GRAD_SIZE &&
       clickPosRow>0 && clickPosRow<BOARD_GRAD_SIZE &&
       (game->gameMapVec[clickPosRow][clickPosCol]==1||game->gameMapVec[clickPosRow][clickPosCol]==-1)){  //代碼解析：game->gameMapVec[clickPosRow][clickPosCol]==1||game->gameMapVec[clickPosRow][clickPosCol]==-1，防止因為5個0(空白)相連也被判勝利
        if(game->isWin(clickPosRow,clickPosCol) && game->gameStatus == PLAYING){
            game->gameStatus = WIN;
            QString str;
            str = game->gameMapVec[clickPosRow][clickPosCol]==1?"黑棋":"白棋";
            QMessageBox::StandardButton btnValue = QMessageBox::information(this,"五子棋嬴家",str+"勝利");
            if(btnValue == QMessageBox::Ok){
                game->startGame(game_type);
                game->gameStatus = PLAYING;
            }

        }
    }
}
//初始化遊戲
void MainWindow::initGame(){
    game = new GameModel();
    QMessageBox::StandardButton select = QMessageBox::question(this,"選擇遊戲模式","YES[玩家VS電腦]  NO[玩家VS玩家]");
    if(select == QMessageBox::Yes){
        game_type = AI;
    }else {
        game_type = MAN;
    }
    game->gameStatus = PLAYING;

    game->startGame(game_type);
    update();
}



void MainWindow::mouseMoveEvent(QMouseEvent* event){
    //通過鼠標的hover確定落子的標記
    int x = event->x();
    int y = event->y();

    //棋盤邊緣不能落子
    if(x>=MARGIN+BLOCK_SIZE/2&&
           x<this->width()-MARGIN-BLOCK_SIZE/2&&
           y>=MARGIN+BLOCK_SIZE/2&&
           y<this->height()-MARGIN-BLOCK_SIZE/2){
        //獲取最近的左上角的點
        int col = (x-MARGIN)/BLOCK_SIZE;
        int row = (y-MARGIN)/BLOCK_SIZE;

        int leftTopPosX = MARGIN+BLOCK_SIZE*col;
        int leftTopPosY = MARGIN+BLOCK_SIZE*row;

        //根據距離算出合適的點擊位置，一共四個點，根據半徑距離選最近的
        clickPosRow = -1; //初始化最終值
        clickPosCol = -1;
        int len = 0;  //計算完後取整就可以了

        selectPos = false;

        //確定一個誤差在範圍內的點，且只可能確定一個出來
        //len：與左上角的點的距離
        len = sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len<POS_OFFSET){
            clickPosRow = row;
            clickPosCol = col;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0){
                selectPos = true;
            }
        }
        //len：與右上角的點的距離
        len = sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY)*(y-leftTopPosY));
        if(len<POS_OFFSET){
            clickPosRow = row;
            clickPosCol = col+1;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0){
                selectPos = true;
            }
        }
        //len：與左下角的點的距離
        len = sqrt((x-leftTopPosX)*(x-leftTopPosX)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len<POS_OFFSET){
            clickPosRow = row+1;
            clickPosCol = col;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0){
                selectPos = true;
            }
        }
        //len：與右下角的點的距離
        len = sqrt((x-leftTopPosX-BLOCK_SIZE)*(x-leftTopPosX-BLOCK_SIZE)+(y-leftTopPosY-BLOCK_SIZE)*(y-leftTopPosY-BLOCK_SIZE));
        if(len<POS_OFFSET){
            clickPosRow = row+1;
            clickPosCol = col+1;
            if(game->gameMapVec[clickPosRow][clickPosCol]==0){
                selectPos = true;
            }
        }
    }
    //存了坐標後也要重繪
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event){
    if(selectPos == false){
        return;
    }else{
        selectPos = false;
    }
    //由人來下棋
    chessOneByPerson();
    if(game_type == AI){ //人機模式
        //AI 下棋
        QTimer::singleShot(AI_THINK_TIME,this,SLOT(chessOneByAI()));
    }
}

void MainWindow::chessOneByPerson(){
    if(clickPosRow!=-1 && clickPosCol!=-1 && game->gameMapVec[clickPosRow][clickPosCol]==0){
        //在遊戲的數據模型中落子
        game->actionByPerson(clickPosRow,clickPosCol);
        //播放落子音效

        //重繪
        update();

    }
}

void MainWindow::chessOneByAI(){
    game->actionByAI(clickPosRow,clickPosCol);
    update();
}
