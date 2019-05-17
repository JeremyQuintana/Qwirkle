//
// Created by ariacelesta on 08/05/19.
//

#include "GameEngine.h"

#define BOARD_LENGTH boardLength

using std::cin;
using std::stoi;

GameEngine::GameEngine() {
    // counter for turns passed in game
    turn = 1;
    inGame = true;
    startGame();
}


//main function that runs the actual game
void GameEngine::startGame() {
    assembleBoard();
    //dealTiles() function needed to assign opening hands and remove these tiles from tile bag
    //loops while there is no winner yet and game is still running
    /*while(inGame){
         takeTurn() calls placeTile() or replaceTile()
            both above call drawTile
         printBoard();
         endTurn();

    }*/
}


//assembles the board according to the size inputted in the console
void GameEngine::assembleBoard(){
    cout << "Please enter board size (MxM): ";
    cin >> boardLength;
    board= new Board[BOARD_LENGTH];
    for (int i=0;i<BOARD_LENGTH;i++){
        board[i]= new BoardRow[BOARD_LENGTH];
        for(int j=0; j<BOARD_LENGTH; j++){
            board[i][j]= new Tile;
        }
    }
    printBoard();
}

void GameEngine::takeTurn() {
    std::cin.clear();
    std::cin.ignore();
    int option = 0;
    bool validated = false;
    std::string playerCommand = "";
    //loops until a valid move has been made
    while (validated == false) {
        //gets input
        std::cout << "> ";
        std::getline(std::cin, playerCommand);

        //checks input for valid keywords
        if(playerCommand.substr(0,5).compare("save ") == 0)          option = 3;
        else if(playerCommand.substr(0,8).compare("replace ") == 0)  option = 2;
        else if(playerCommand.substr(0,6).compare("place ") == 0
                && playerCommand.substr(8,4).compare(" at ") == 0)   option = 1;

        else std::cout << "Error - Invalid option" << std::endl;

        //calls relevant functions and if unsuccesful stays in loop
        if(option == 1) {
          Tile tile = Tile(playerCommand.at(6), playerCommand.at(7) - '0');
          if (placeTile(tile, playerCommand.substr(12,2))) validated = true;
        } else if(option == 2) {
          Tile tile = Tile(playerCommand.at(8), playerCommand.at(9) - '0');
          if (replaceTile(tile)) validated = true;;
        } else if(option == 3) {
          saveGame();
          validated= true;
        }
        option = 0;
    }
}

bool GameEngine::placeTile(Tile tile, std::string coordinate) {

    // row player asked for
    char row = coordinate.at(0);
    int destinationRow = row - 65;
    // column player asked for
    std::string column = coordinate.substring(1);
    int destinationColumn = std::stoi(column);
    // copies of these to use as counters
    int currentRow = destinationRow;
    int currentColumn = destinationColumn;
    Tile currentTile = tile;
    // bool values used for checksm and rule variable -> -1 is colour, 1 is shape
    bool emptyNorth = false, emptySouth = false, emptyEast = false, emptyWest = false;
    int ruleNorth = 0, ruleSouth = 0, ruleEast = 0, ruleWest = 0;
    // required colour and/or shape
    std::string reqColour = tile->getValue().at(0); // eg. "R"
    std::string reqShape = tile->getValue().at(1); // eg. "3"

    bool isValid = true;
    // check coordinate exists - needs to be changed for dynamic boards in future
    if(destinationRow < 65 || destinationRow > 65 + BOARD_LENGTH || destinationColumn < 0 || destinationColumn > BOARD_LENGTH) isValid = false;
    // check coordinate is not currently occupied
    if(board[destinationRow][destinationColumn]!= NULL) isValid = false;
    // check tile is placed adjacent to an existing tile after turn 1
    // assuming turn denotes turns passed
    emptyNorth = (board[destinationRow-1][destinationColumn] == NULL || destinationRow == 0) ? true : false;
    emptySouth = (board[destinationRow+1][destinationColumn] == NULL || destinationRow == (BOARD_LENGTH - 1)) ? true : false;
    emptyEast = (board[destinationRow][destinationColumn+1] == NULL || destinationColumn == (BOARD_LENGTH - 1)) ? true : false;
    emptyWest = (board[destinationRow][destinationColumn-1] == NULL || destinationColumn == 0) ? true : false;
    if(turn > 1 && emptyN && emptyS && emptyE && emptyW) isValid = false;

    // check north
    if(!emptyNorth) {
        currentTile = board[currentRow-1][currentColumn];
        if(currentTile->getValue().at(0).compare(reqColour)) ruleNorth--;
        if(currentTile->getValue().at(1).compare(reqShape))  ruleNorth++;
        if(ruleNorth == 0) isValid = false;
    }
    while(currentTile != NULL && (currentRow-1) >= 0) {
        currentTile = board[currentRow-1][currentColumn];
        if(tile->getValue().compare(currentTile->getValue()) == 0) isValid = false;
        currentRow--;
    }
    // check south
    if(!emptySouth) {
        currentTile = board[currentRow+1][currentColumn];
        if(currentTile->getValue().at(0).compare(reqColour)) ruleSouth--;
        if(currentTile->getValue().at(1).compare(reqShape))  ruleSouth++;
        if(ruleSouth == 0) isValid = false;
    }
    while(currentTile != NULL && (currentRow+1) <= BOARD_LENGTH) {
        currentTile = board[currentRow+1][currentColumn];
        if(tile->getValue().compare(currentTile->getValue()) == 0) isValid = false;
        currentRow++;
    }
    // if both exist, determine if the same rule
    if(!emptyNorth && !emptySouth) {
        if(ruleNorth != ruleSouth) isValid = false;
        // need method to determine if any tiles in south exist in north,if so isValid = false

        // implement
    }

    // check east
    if(!emptyEast) {
        currentTile = board[currentRow][currentColumn+1];
        if(currentTile->getValue().at(0).compare(reqColour)) ruleEast--;
        if(currentTile->getValue().at(1).compare(reqShape))  ruleEast++;
        if(ruleEast == 0) isValid = false;
    }
    while(currentTile != NULL && (currentColumn+1) <= BOARD_LENGTH) {
        currentTile = board[currentRow][currentColumn+1];
        if(tile->getValue().compare(currentTile->getValue()) == 0) isValid = false;
        currentColumn++;
    }
    // check west
    if(!emptyWest) {
        currentTile = board[currentRow][currentColumn-1];
        if(currentTile->getValue().at(0).compare(reqColour)) ruleWest--;
        if(currentTile->getValue().at(1).compare(reqShape))  ruleWest++;
        if(ruleWest == 0) isValid = false;
    }
    while(currentTile != NULL && (currentColumn+1) <= BOARD_LENGTH) {
        currentTile = board[currentRow][currentColumn+1];
        if(tile->getValue().compare(currentTile->getValue()) == 0) isValid = false;
        currentColumn++;
    }
    // if both exist, determine if the same rule
    if(!emptyEast && !emptyWest) {
        if(ruleEast != ruleWest) isValid = false;
        // need method to determine if any tiles in east exist in west,if so isValid = false

        //implement
    }


    if(isValid) board[destinationRow][destinationColumn] = tile;
    return isValid;
}

void GameEngine::saveGame(){

    bool
    while











}

void GameEngine::calcScore() {

}

bool GameEngine::replaceTile(Tile tile) {
    bool successful = false;
    if (playerList[currentPlayer]->getTilePtr(tile) != nullptr){
      playerList[currentPlayer]->removeTile(tile);
      playerList[currentPlayer]->addTile(tileBag.get(0));
      tileBag.deleteFront();
      successful = true;
    }
    else std::cout << "Error - Tile Not Found" << std::endl;

    return successful;
}

void GameEngine::drawTile() {

}

void GameEngine::endTurn() {
    turn++;
}

//prints the entire board to the system console including the tiles placed
void GameEngine::printBoard() {
    String initial = "   ";
    if(boardLength>10){
        initial= "  ";
    }
    cout << initial;
    String prefix= " ";
    String postfix= " ";
    for(int k=0;k<BOARD_LENGTH;k++) {
        if(k>10){
            prefix= "";
        }
        cout << prefix << k << postfix;
    }
    cout << endl;
    //for(int k=0;k<BOARD_LENGTH;k++) {
    //    cout << "----";
    //}
    //cout << "-" << endl;
    char alfa= 'A';
    for (int i = 0; i < BOARD_LENGTH; i++) {

        cout<< alfa;
        cout << " |";
        for (int j = 0; j < BOARD_LENGTH; j++) {
            String value = "  ";
            if (board[i][j]->getValue().compare("0")>0) {
              value = board[i][j]->getValue();
            }
            cout << value << "|";
        }
        alfa+=1;
        cout << endl;

    }
    //for(int k=0;k<BOARD_LENGTH;k++) {
    //    cout << "---";
    //}
    cout << endl;
}
