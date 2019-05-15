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

}

void GameEngine::placeTile(Tile tile) {
}

void GameEngine::replaceTile(Tile tile) {

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
