//
// Created by ariacelesta on 08/05/19.
//

#include "GameEngine.h"

#define BOARD_LENGTH boardLength

using std::cin;
using std::stoi;

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
        // take player input
        std::cin >> playerCommand;
        std::string shouldBeAt = playerCmmand.substring(8,4);
        // below checks assume tile validation was done on player side
        // check standard format for 'placeTile' operation
        if(playerCommand.starts_with(std::string("place ")) && shoudlBeAt.compare(std::string(" at ")) == 0) {
            char rowAsChar = playerCommand.at(12);
            char rowAsInt = (Integer)rowAChar;
            std::string columnAsString = playerCommand.substring(13);
            int columnAsInt = std::stoi(columnAsString);
            // check coordinate exists - needs to be changed for dynamic boards in future
            if(rowAsInt >= 65 && rowAsInt <= 65 + BOARD_LENGTH && columnAsInt >= 0 && columnAsInt <= BOARD_LENGTH) {
                // check coordinate is not currently occupied
                if(board[rowAsInt][columnAsInt]!= NULL) {
                    // // check it's adjacent to at least 1 tile
                    // // also needs changing for dynamic board
                    // bool existsN = (board[rowAsInt-1][columnAsInt] == NULL || rowAsInt == 0) ? false : true;
                    // bool existsS = (board[rowAsInt+1][columnAsInt] == NULL || rowAsInt == (BOARD_LENGTH - 1)) ? false : true;
                    // bool existsE = (board[rowAsInt][columnAsInt+1] == NULL || columnAsInt == (BOARD_LENGTH - 1)) ? false : true;
                    // bool existsW = (board[rowAsInt][columnAsInt-1] == NULL || columnAsInt == 0) ? false : true;
                    // if(existsN || existsS || existsE || existsW) {
                    option = 1;
                    validated = true;
                    // }
                    // else {
                    //     errorMessage = "Error - Tile must be placed adjacent to an existing tile";
                    // }
                }
                else {
                    errorMessage = "Error - A tile already exists at ";
                    errorMessage.append(playerCommand.substring(12));
                }
            }
            else {
                errorMessage = "Error - Invalid coordinate";
            }
        }
        // check standard format for 'replaceTile' operation
        if(playerCommand.starts_with(std::string("replace "))) {
            option = 2;
            validated = true;
        }
        else {
            errorMessage = "Error - Invalid command\nCommand should be in the format: place <tile> at <coordinate>";
        }
        std::cout << errorMessage << std::endl << "> ";
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
    // row player asked for
    char row = coordinate.at(0);
    int destinationRow = row - 65;
    // column player asked for
    std::string column = coordinate.substring(1);
    int destinationColumn = std::stoi(column);
    // copies of these to use as counters
    int currentRow = destinationRow;
    int currentColumn = destinationColumn;
    // required colour and/or shape
    std::string reqColour = tile.getValue().at(0); // eg. "R"
    std::string reqShape = tile.getValue().at(1); // eg. "3"

    bool existsN = (board[destinationRow-1][destinationColumn] == NULL || destinationRow == 0) ? false : true;
    bool existsS = (board[destinationRow+1][destinationColumn] == NULL || destinationRow == (BOARD_LENGTH - 1)) ? false : true;
    bool existsE = (board[destinationRow][destinationColumn+1] == NULL || destinationColumn == (BOARD_LENGTH - 1)) ? false : true;
    bool existsW = (board[destinationRow][destinationColumn-1] == NULL || destinationColumn == 0) ? false : true;

    bool
    while











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
