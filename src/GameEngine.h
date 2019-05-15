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
    void printBoard();
    void startGame();
    int boardLength;
    void placeTile();
    void pickTile();
    void playTile();
    void cycleTurn();
    void assembleBoard();
    void placeTile(Tile tile);
    void replaceTile(Tile tile);
    void drawTile();
    void endTurn();
};

#endif //SRC_GAMEENGINE_H
