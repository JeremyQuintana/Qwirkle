//
// Created by ariacelesta on 08/05/19.
//

#ifndef SRC_GAMEENGINE_H
#define SRC_GAMEENGINE_H

#include "Tile.h"
#include "Player.h"
#include "LinkedList.h"
#include "TileCodes.h"

#include "fstream"

typedef Tile** Board;
typedef Tile* BoardRow;

using std::cout;
using std::endl;

class GameEngine {
public:

    GameEngine(std::string playerList[], int totalPlayers);
    ~GameEngine();

private:
    Board* board;
    int boardLength;
    int turn;
    bool inGame;
    std::string playerCommand;
    LinkedList tileBag;
    Player* *playerList;
    int totalPlayers;
    int currentPlayer;
    void startGame();
    void assembleBoard();
    void takeTurn();
    bool placeTile(Tile tile, std::string coordinate);
    void calcScore();
    bool replaceTile(Tile tile);
    void drawTile();
    void endTurn();
    std::string printBoard();
    void dealTiles();
    void saveGame(std::string fileName);
};

#endif //SRC_GAMEENGINE_H
