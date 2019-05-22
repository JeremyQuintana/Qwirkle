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
    GameEngine(int totalPlayers, int rowLength, int colLength, String playerNames[],
            int playerScores[], String playerHands[], String board[], String bag, int turn);
    ~GameEngine();

private:
    Board* board;
    Board* dynamicBoard;
    int boardLength;
    int rowLength;
    int colLength;
    int turn;
    bool inGame;
    std::string playerCommand;
    LinkedList tileBag;
    Player* *playerList;
    int totalPlayers;
    int currentPlayer;
    void startGame();
    void assembleBoard();
    void assembleDynamicBoard();
    bool takeTurn();
    bool placeTile(Tile tile, std::string coordinate);
    bool replaceTile(Tile tile);
    void drawTile();
    void endTurn();
    std::string printBoard();
    void dealTiles();
    void saveGame(std::string fileName);
    void updateDynamicBoard(int, int);
    String boardToString();
    void stringToBoard();
};

#endif //SRC_GAMEENGINE_H
