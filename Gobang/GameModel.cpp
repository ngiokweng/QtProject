#include "GameModel.h"
#include <time.h>
#include <stdlib.h>

GameModel::GameModel(){

}

void GameModel::startGame(GameType type){
    gameType = type;
    //初始化棋盤
    gameMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;i++){
        std::vector<int> lineBoard;
        for(int j=0;j<BOARD_GRAD_SIZE;j++){
            lineBoard.push_back(0);
        }
        gameMapVec.push_back(lineBoard);
    }
    //如果是AI模式，需要初始化評分數組
    if(gameType == AI){
        scoreMapVec.clear();
        for(int i=0;i<BOARD_GRAD_SIZE;i++){
            std::vector<int> lineScores;
            for(int j=0;j<BOARD_GRAD_SIZE;j++){
                lineScores.push_back(0);
            }
            scoreMapVec.push_back(lineScores);
        }
    }
    //輪到黑方下棋為true，反之
    playerFlag = true;
}

void GameModel::actionByPerson(int row, int col){
    updateGameMap(row,col);
}
void GameModel::updateGameMap(int row, int col){
    if(playerFlag){
        gameMapVec[row][col] = 1;
    }else{
        gameMapVec[row][col] = -1;
    }
    //換手
    playerFlag = !playerFlag;
}

bool GameModel::isWin(int row,int col){
    /*判斷下棋點的水平、垂直、左斜、右斜方中
     * 有沒有5子相連的情況，如有則贏
     */
    for(int i=0;i<5;i++){
        //先判斷水平方向是否有5子相連
        if(row>0 && row<BOARD_GRAD_SIZE &&
           col-i>0 && col-i+4<BOARD_GRAD_SIZE &&
           gameMapVec[row][col-i] == gameMapVec[row][col-i+1] &&
           gameMapVec[row][col-i] == gameMapVec[row][col-i+2] &&
           gameMapVec[row][col-i] == gameMapVec[row][col-i+3] &&
           gameMapVec[row][col-i] == gameMapVec[row][col-i+4]){
            return true;
        }
        //先判斷垂直方向是否有5子相連
        if(row-i>0 && row-i+4<BOARD_GRAD_SIZE &&
           col>0 && col<BOARD_GRAD_SIZE &&
           gameMapVec[row-i][col] == gameMapVec[row-i+1][col] &&
           gameMapVec[row-i][col] == gameMapVec[row-i+2][col] &&
           gameMapVec[row-i][col] == gameMapVec[row-i+3][col] &&
           gameMapVec[row-i][col] == gameMapVec[row-i+4][col]){
            return true;
        }
        //先判斷"/"方向是否有5子相連，左下->右上
        if(
           row-i>0 && row-i+4<BOARD_GRAD_SIZE &&
           col+i-4>0 && col+i<BOARD_GRAD_SIZE &&
           gameMapVec[row-i][col+i] == gameMapVec[row-i+1][col+i-1] &&
           gameMapVec[row-i][col+i] == gameMapVec[row-i+2][col+i-2] &&
           gameMapVec[row-i][col+i] == gameMapVec[row-i+3][col+i-3] &&
           gameMapVec[row-i][col+i] == gameMapVec[row-i+4][col+i-4]){
            return true;
        }
        //先判斷"\"方向是否有5子相連，右下->左上
        if(row-i>0 && row-i+4<BOARD_GRAD_SIZE &&
           col-i>0 && col-i+4<BOARD_GRAD_SIZE &&
           gameMapVec[row-i][col-i] == gameMapVec[row-i+1][col-i+1] &&
           gameMapVec[row-i][col-i] == gameMapVec[row-i+2][col-i+2] &&
           gameMapVec[row-i][col-i] == gameMapVec[row-i+3][col-i+3] &&
           gameMapVec[row-i][col-i] == gameMapVec[row-i+4][col-i+4]){
            return true;
        }

    }
    return false;
}

//計算每格分數函數
void GameModel::calculateScore(){
    //統計玩家或者電腦連成的子
    int personNum = 0; //玩家連成子的個數
    int botNum = 0;   //AI連成子的個數
    int emptyNum = 0;   //各方向空白位的個數

    //清空評分數組
    scoreMapVec.clear();
    for(int i=0;i<BOARD_GRAD_SIZE;i++){
        std::vector<int> lineScores;
        for(int j=0;j<BOARD_GRAD_SIZE;j++){
            lineScores.push_back(0);
        }
        scoreMapVec.push_back(lineScores);
    }
    //計分
    /*計分個人理解：
     * 遍歷每一個格子，判斷哪些是空白的點(即為0的點)，以該點為中心，判斷周圍的八個點向外延伸的四格裡，
     * 有多少個是黑子、白子、空白，以此作為依據來評分。下方算法是以守為主，所以守的分數>攻的分數
     */
    for(int row=0;row<BOARD_GRAD_SIZE;row++){
        for(int col=0;col<BOARD_GRAD_SIZE;col++){
            //空白點才算
            if(row>0 && col>0 && gameMapVec[row][col]==0){
                //遍歷周圍8個方向
                for(int y=-1;y<=1;y++){
                    for(int x=-1;x<=1;x++){
                        //重置
                        personNum = 0;
                        botNum = 0;
                        emptyNum = 0;
                        //原坐標不算
                        if(!(y==0 && x==0)){
                            //每個方向延伸4個子

                            //對玩家黑子評分(正反兩個方向)
                            for(int i=1;i<=4;i++){
                                if(row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                   col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                   gameMapVec[row+i*y][col+i*x]==1){ //真人玩家的子
                                    personNum++;
                                }else if(row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                         col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                         gameMapVec[row+i*y][col+i*x]==0){ //空白位
                                    emptyNum++;
                                    break;
                                }else{ //出邊界，或有白子
                                    break;
                                }
                            }
                            for(int i=1;i<=4;i++){
                                if(row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                   col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                   gameMapVec[row-i*y][col-i*x]==1){ //真人玩家的子
                                    personNum++;
                                }else if(row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                         col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                         gameMapVec[row-i*y][col-i*x]==0){ //空白位
                                    emptyNum++;
                                    break;
                                }else{ //出邊界，或有白子
                                    break;
                                }
                            }
                            if(personNum == 1){                 //殺2
                                scoreMapVec[row][col]+=10;
                            }else if(personNum == 2){           //殺3
                                if(emptyNum == 1)
                                    scoreMapVec[row][col]+=30;
                                else if(emptyNum == 2)
                                    scoreMapVec[row][col]+=40;
                            }else if(personNum == 3){           //殺4
                                //量變空位不一樣，優先級不一樣
                                if(emptyNum == 1)
                                    scoreMapVec[row][col]+=60;
                                else if(emptyNum == 2)
                                    scoreMapVec[row][col]+=110;
                            }else if(personNum == 4){           //殺5
                                scoreMapVec[row][col]+=10100;
                            }

                            //進行一次清空
                            emptyNum = 0;

                            //對AI白子評分
                            for(int i=1;i<=4;i++){
                                if(row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                   col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                   gameMapVec[row+i*y][col+i*x]==-1){ //AI的子
                                    botNum++;
                                }else if(row+i*y>0 && row+i*y<BOARD_GRAD_SIZE &&
                                         col+i*x>0 && col+i*x<BOARD_GRAD_SIZE &&
                                         gameMapVec[row+i*y][col+i*x]==0){ //空白位
                                    emptyNum++;
                                    break;
                                }else{ //出邊界
                                    break;
                                }
                            }
                            for(int i=1;i<=4;i++){
                                if(row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                   col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                   gameMapVec[row-i*y][col-i*x]==-1){ //AI的子
                                    botNum++;
                                }else if(row-i*y>0 && row-i*y<BOARD_GRAD_SIZE &&
                                         col-i*x>0 && col-i*x<BOARD_GRAD_SIZE &&
                                         gameMapVec[row-i*y][col-i*x]==0){ //空白位
                                    emptyNum++;
                                    break;
                                }else{ //出邊界
                                    break;
                                }
                            }
                            if(botNum == 0){
                                scoreMapVec[row][col]+=5;  //活1
                            }else if(botNum == 1){
                                scoreMapVec[row][col]+=10; //活2
                            }else if(botNum == 2){         //活3
                                if(emptyNum == 1)
                                    scoreMapVec[row][col]+=25;
                                else if(emptyNum == 2)
                                    scoreMapVec[row][col]+=50;
                            }else if(botNum == 3){         //活4
                                if(emptyNum == 1)
                                    scoreMapVec[row][col]+=55;
                                else if(emptyNum == 2)
                                    scoreMapVec[row][col]+=100;
                            }else if(botNum >= 4){         //活5
                                scoreMapVec[row][col]+=20000;
                            }


                        }
                    }
                }
            }
        }
    }

}
//AI執行下棋
void GameModel::actionByAI(int &clickRow,int &clickCol){
    //計算評分
    calculateScore();

    //從評分中找出最大分數的位置
    int maxScore = 0;
    std::vector<std::pair<int,int>> maxPoints;
    for(int row = 1;row<BOARD_GRAD_SIZE;row++){
        for(int col = 1;col<BOARD_GRAD_SIZE;col++){
            //前提是這個坐標是空的
            if(gameMapVec[row][col] == 0){
                if(scoreMapVec[row][col]>maxScore){     //找最大數和坐標
                    maxPoints.clear();
                    maxScore = scoreMapVec[row][col];
                    maxPoints.push_back(std::make_pair(row,col));
                }else if(scoreMapVec[row][col] == maxScore){   //如果有多個最大值就將他們存儲起來，在後面的代碼隨機抽1個
                    maxPoints.push_back(std::make_pair(row,col));
                }
            }
        }
    }
    //隨機落子，如果有多個點的話
    srand((unsigned)time(0));
    int index = rand()%maxPoints.size();
    std::pair<int,int> pointPair = maxPoints.at(index);
    clickRow = pointPair.first;
    clickCol = pointPair.second;
    updateGameMap(clickRow,clickCol);
}
