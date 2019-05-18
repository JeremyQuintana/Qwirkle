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
    playerList = new Player*[4];
    //should have a constructor to initialise the player names from qwirkle class
    playerList[0] = new Player("1", new LinkedList);
    playerList[1] = new Player("2", new LinkedList);
    dealTiles();
    inGame = true;
    //loops while there is no winner yet and game is still running
    while(inGame){
      std::cout << std::endl
      << playerList[currentPlayer]->getName()
      << ", it's your turn" << std::endl;

      for (int i = 0; i < 4 && playerList[i] != nullptr; i++){
        std::cout
        << "Score for " << playerList[i]->getName()
        << ": " << playerList[i]->getScore() << std::endl;

      }
      printBoard();
      std::cout
      << "Your hand is:"                           << std::endl
      << playerList[currentPlayer]->handToString() << std::endl << std::endl;

      takeTurn();
      endTurn();
    }
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
    std::cin.clear();
    std::cin.ignore();
}

void GameEngine::takeTurn() {
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
          saveGame(playerCommand.substr(5, playerCommand.length()-5));
          validated= true;
        }
        option = 0;
    }
}

bool GameEngine::placeTile(Tile tile, std::string coordinate) {
  return false;
}

void GameEngine::saveGame(std::string fileName){
  std::ofstream outFile;
  outFile.open(fileName);

  //loop to print players and deets to file
  //prints max 4 players but not necissarily needs to be 4
  for (int i = 0; i < 4 && playerList[i] != nullptr; i++){
    outFile
      << playerList[i]->getName()      << endl
      << playerList[i]->getScore()     << endl
      << playerList[i]->handToString() << endl;
  }

  //TODO
  //print board, possibly turn the printBoard function to return String

  outFile << tileBag.listToString() << endl;
  outFile << playerList[currentPlayer]->getName() << endl;

  outFile.close();
  std::cout << std::endl << "Game successfully saved" << std::endl;
}

void GameEngine::calcScore() {

}

bool GameEngine::replaceTile(Tile tile) {
    bool successful = false;
    if (playerList[currentPlayer]->getTilePtr(tile) != nullptr){
      playerList[currentPlayer]->removeTile(tile);
      Tile* tile = tileBag.get(0);
      playerList[currentPlayer]->addTile(tile);
      tileBag.deleteTile(*tile);
      successful = true;
    }
    else std::cout << "Error - Tile Not Found" << std::endl;

    return successful;
}

void GameEngine::drawTile() {

}

void GameEngine::endTurn() {
    turn= abs(turn-1);

    //increment to next player
    currentPlayer++;
    if (playerList[currentPlayer] == nullptr) currentPlayer = 0;

    //end game if tileBag is empty
    if (tileBag.size() == 0) inGame = false;

    //TODO check if theres valid moves
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

        cout << alfa;
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

void GameEngine::dealTiles(){
  //create tileBag
  Colour tileColours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  Shape tileShapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

  for (Colour colour : tileColours){
    for (Shape shape : tileShapes){
      Tile* tile = new Tile(colour, shape);
      tileBag.addFront(tile);
    }
  }

  //TODO need a shuffle function for the linked list here

  //draw from tileBag into each players hand;
  for (int i = 0; i < 4 && playerList[i] != nullptr; i++){
    for (int x = 0; x < 6; x++){
      Tile* tile = tileBag.get(0);
      playerList[i]->addTile(tile);
      tileBag.deleteTile(*tile);
    }
  }
}
