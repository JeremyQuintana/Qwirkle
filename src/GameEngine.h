//
// Created by ariacelesta on 08/05/19.
//

#ifndef SRC_GAMEENGINE_H
#define SRC_GAMEENGINE_H

#include "Tile.h"
#include "Player.h"

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
    std::string playerCommand;
    LinkedList tileBag;
    Player* playerList;
    int currentPlayer;
    void startGame();
    void assembleBoard();
    void takeTurn();
    void placeTile(Tile tile, std::string coordinate);
    void calcScore();
    void replaceTile(Tile tile);
    void drawTile();
    void endTurn();
    void printBoard();
};

#endif //SRC_GAMEENGINE_H
