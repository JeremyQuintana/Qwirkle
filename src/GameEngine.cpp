//
// Created by ariacelesta on 08/05/19.
//

#include "GameEngine.h"

#define BOARD_LENGTH boardLength

using std::cin;

GameEngine::GameEngine(std::string playerListNames[4]) {
    turn= 0;
    inGame= true;
    playerList = new Player*[4];

    for (int i = 0; i < 4 && playerListNames[i] != ""; i++)
      playerList[i] = new Player(playerListNames[i], new LinkedList);

    assembleBoard();
    dealTiles();
    startGame();
}

//main function that runs the actual game
void GameEngine::startGame() {
    //loops while there is no winner yet and game is still running
    inGame = true;
    while(inGame){
      std::cout << std::endl
      << playerList[currentPlayer]->getName()
      << ", it's your turn" << std::endl;

      for (int i = 0; i < 4 && playerList[i] != nullptr; i++){
        std::cout
        << "Score for " << playerList[i]->getName()
        << ": " << playerList[i]->getScore() << std::endl;

      }
      std::cout << printBoard() << std::endl;
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

  outFile << printBoard() << endl;
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
    if (tileBag.size() == 0){
      inGame = false;

      //loops through all players printing their deets and finding the winner
      std::string winner = "";
      int winningScore = 0;
      for (int i = 0; i < 4 && playerList[i] != nullptr; i++){
        //prints player deets
        std::cout << "Score for " << playerList[i]->getName() << std::endl;
        std::cout << ": " << playerList[i]->getScore() << std::endl;

        //calcs if the player is a winner
        if (playerList[i]->getScore() > winningScore){
          winner = playerList[i]->getName();
          winningScore = playerList[i]->getScore();
        }
        else if (playerList[i]->getScore() == winningScore){
          if (winner != "") winner = winner + " & " + playerList[i]->getName();
          else winner = playerList[i]->getName();
        }
      }
      std::cout << "Player " << winner << " won!" << std::endl << std::endl;
    }

    //TODO check if theres valid moves
}

//prints the entire board to the system console including the tiles placed
std::string GameEngine::printBoard() {
    std::string boardStr = "";
    String initial = "   ";
    if(boardLength>10){
        initial= "  ";
    }
    boardStr = initial;
    String prefix= " ";
    String postfix= " ";
    for(int k=0;k<BOARD_LENGTH;k++) {
        if(k>10){
            prefix= "";
        }
        boardStr += prefix + std::to_string(k) + postfix;
    }
    //for(int k=0;k<BOARD_LENGTH;k++) {
    //    cout << "----";
    //}
    //cout << "-" << endl;
    char alfa= 'A';
    for (int i = 0; i < BOARD_LENGTH; i++) {
        boardStr += "\n";
        boardStr += alfa;
        boardStr += " |";
        for (int j = 0; j < BOARD_LENGTH; j++) {
            String value = "  ";
            if (board[i][j]->getValue().compare("0")>0) {
              value = board[i][j]->getValue();
            }
            boardStr += value + "|";
        }
        alfa+=1;

    }
    //for(int k=0;k<BOARD_LENGTH;k++) {
    //    cout << "---";
    //}

    return boardStr;
}

void GameEngine::dealTiles(){
  //create tileBag
  Colour tileColours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  Shape tileShapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

  for (Colour colour : tileColours){
    for (Shape shape : tileShapes){
      int copies = 2;
      for (int i = 0; i < copies; i++){
        Tile* tile = new Tile(colour, shape);
        tileBag.addFront(tile);
      }
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
  // std::cout << playerList[0]->handToString() << std::endl;
}
