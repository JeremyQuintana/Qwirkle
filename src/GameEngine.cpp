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
        for(int j=0; j<BOARD_LENGTH; j++){
            board[i][j]= new Tile;
        }
    }
    printBoard();
}

void GameEngine::takeTurn() {
    std::cout << "> ";
    int option = 0;
    bool validated = false;
    std::string errorMessage = "Error";
    while (validated == false) {
        std::cin >> playerCommand;
        std::string shouldBeAt = playerCmmand.substring(8,4);
        if(playerCommand.starts_with(std::string("place ")) && shoudlBeAt.compare(std::string(" at ")) == 0) {
            if(/*check coordinate exists*/) {
                if(/* check coordinate is not currently occupied*/) {
                    // also need a check to make sure it's adjacent to at least 1 tile
                    option = 1;
                    validated = true;
                }
                else {
                    errorMessage = "Error - A tile already exists at ";
                    errorMessage.append(playerCommand.substring(12));
                }
            }
            else {
                errorMessage = "Error - Invalid coordinate"
            }
        }
        if(playerCommand.starts_with(std::string("replace "))) {
            option = 2;
            validated = true;
        }
        else {
            std::cout << "Error - Invalid command" << std::endl
        << "Command should be in the format: place <tile> at <coordinate>";
        }
        std::cout << std::endl << "> ";
        std::cin.clear();
        std::cin.ignore();
    }
    if(option == 1) {
        // does this work??
        placeTile(Tile(Colour playerCommand.at(6), Shape playerCommand.at(7)), playerCommand.substring(12));
    }
    if(option == 2) {
        // as above ^
        replaceTile(Tile(Colour playerCommand.at(8), Shape playerCommand.at(9)));
    }
}

void GameEngine::placeTile(Tile tile, std::string coordinate) {
    char row = coordinate.at(0);
    int destinationRow = row - 65;
    int destinationColumn = (Integer)coordinate.substring(1);
    int currentRow = destinationRow;
    int currentColumn = destinationColumn;
    std::string reqColour = tile.getValue().at(0);
    std::string reqShape = tile.getValue().at(1);

    








}

void GameEngine::replaceTile(Tile tile) {
    playerList[currentPlayer].removeTile(tile);
    playerLIst[currentPlayer].addTile(tileBag.get(0));
    tileBag.deleteFront();
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
