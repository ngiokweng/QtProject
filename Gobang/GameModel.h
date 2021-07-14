#ifndef GAMEMODEL_H
#define GAMEMODEL_H

////////  五子棋遊戲模型  ////////

#include <vector>

//遊戲類型，人人or人機
enum GameType{
    MAN,
    AI  //人機對戰模式
};

enum GameStatus{
    PLAYING,
    WIN,
    DEAD
};

//棋盤尺寸
const int BOARD_GRAD_SIZE = 15;
const int MARGIN = 30; //棋盤邊緣空隙
const int CHESS_RADIUS = 15; //棋子半徑
const int MARK_SIZE = 6; //落子標記邊長
const int BLOCK_SIZE = 40; //格子大小
const int POS_OFFSET = BLOCK_SIZE*0.4; //鼠標點擊的模糊距離上限

const int AI_THINK_TIME = 100; //AI下棋思考時間

class GameModel{
public:
    GameModel();
public:
    //儲存當前遊戲棋盤和棋子的情況，空白為0，黑子1，白子-1
    std::vector<std::vector<int>> gameMapVec;

    //儲存各個點位的評分情況，作為AI下棋依據
    std::vector<std::vector<int>> scoreMapVec;

    //標示下棋方，true黑
    bool playerFlag;

    GameType gameType; //遊戲模式：人機 / 人人

    GameStatus gameStatus; //遊戲狀態

    void startGame(GameType type);

    void actionByPerson(int row, int col);
    void updateGameMap(int row, int col);
    bool isWin(int row,int col);
    void calculateScore(); //計算每格分數函數

    void actionByAI(int &clickRow,int &clickCol); //AI執行下棋
};

#endif // GAMEMODEL_H
