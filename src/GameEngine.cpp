//
// Created by ariacelesta on 08/05/19.
//

#include "GameEngine.h"

#define BOARD_LENGTH boardLength

using std::cin;

GameEngine::GameEngine() {
    turn= 0;
    inGame= true;
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
  return false;
}

void GameEngine::saveGame(){

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
    turn= abs(turn-1);
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
            if (board[i][j]!=nullptr) {
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
