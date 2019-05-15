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
    Tile* tileBagOne;
    Tile* tileBagTwo;
    void printBoard();
    void startGame();
    void placeTile();
    void pickTile();
    void playTile();
    void cycleTurn();
    void assembleBoard();
};

#endif //SRC_GAMEENGINE_H
