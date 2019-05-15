//
// Created by ariacelesta on 08/05/19.
//

#ifndef SRC_GAMEENGINE_H
#define SRC_GAMEENGINE_H

#include "Tile.h"

typedef Tile** Board;
typedef Tile* BoardRow;

using std::cout;
using std::endl;

class GameEngine {
public:

    GameEngine();
    ~GameEngine();

private:
    Board* board;
    int boardLength;
    int turn;
    bool inGame;
    LinkedList tileBag;
    Player* playerList;
    void printBoard();
    void startGame();
    int boardLength;
    void assembleBoard();
    void takeTurn();
    void placeTile(Tile tile);
    void calcScore();
    void replaceTile(Tile tile);
    void drawTile();
    void endTurn();
};

#endif //SRC_GAMEENGINE_H
