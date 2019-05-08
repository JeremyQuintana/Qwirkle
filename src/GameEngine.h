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
    void printBoard();
    void startGame();
    int boardLength;
};

#endif //SRC_GAMEENGINE_H
