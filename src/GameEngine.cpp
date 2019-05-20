//
// Created by ariacelesta on 08/05/19.
//

#include "GameEngine.h"

#define BOARD_LENGTH boardLength
#define DEFAULT_BOARD_LENGTH 3

using std::cin;
using std::stoi;

GameEngine::GameEngine(std::string playerListNames[], int totalPlayers) {
    turn= 0;
    inGame= true;
    playerList = new Player*[totalPlayers];
    currentPlayer= 0;
    this->totalPlayers= totalPlayers;

    for (int i = 0; i < totalPlayers; i++)
      playerList[i] = new Player(playerListNames[i], new LinkedList);

    assembleDynamicBoard();
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

      for (int i = 0; i < totalPlayers; i++){
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
    }
    std::cin.clear();
    std::cin.ignore();
}

void GameEngine::assembleDynamicBoard(){
    rowLength= DEFAULT_BOARD_LENGTH;
    colLength= DEFAULT_BOARD_LENGTH;
    dynamicBoard= new Board[rowLength];
    for (int i=0;i<rowLength;i++){
        dynamicBoard[i]= new BoardRow[colLength];
    }
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

    // row player asked for
    char row = coordinate.at(0);
    int destinationRow = row - 65;
    // column player asked for
    std::string column = coordinate.substr(1);
    int destinationColumn = std::stoi(column);
    // copies of these to use as counters
    int currentRow = destinationRow;
    int currentColumn = destinationColumn;
    int comparatorRow = destinationRow;
    int comparatorColumn = destinationColumn;
    Tile* currentTile = board[destinationRow][destinationColumn];
    Tile* comparatorTile = board[destinationRow][destinationColumn];
    // bool values used for checks and rule variables -> -1 is colour, 1 is shape
    bool emptyNorth = false, emptySouth = false, emptyEast = false, emptyWest = false;
    int ruleNorth = 0, ruleSouth = 0, ruleEast = 0, ruleWest = 0;
    // required colour and/or shape
    char reqColour = tile.getValue().at(0);
    char reqShape = tile.getValue().at(1);

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
    if(turn > 1 && emptyNorth && emptySouth && emptyEast && emptyWest) isValid = false;

    // check north
    if(!emptyNorth) {
        currentRow = destinationRow;
        currentTile = board[currentRow-1][destinationColumn];
        if(currentTile->getValue().at(0) == reqColour) ruleNorth--;
        if(currentTile->getValue().at(1) == reqShape)  ruleNorth++;
        if(ruleNorth == 0) isValid = false;
    }
    while(currentTile != NULL && (currentRow-1) >= 0) {
        currentTile = board[currentRow-1][destinationColumn];
        if(tile.getValue().compare(currentTile->getValue()) == 0) isValid = false;
        currentRow--;
    }
    // check south
    if(!emptySouth) {
        currentRow = destinationRow;
        currentTile = board[currentRow+1][destinationColumn];
        if(currentTile->getValue().at(0) == reqColour) ruleSouth--;
        if(currentTile->getValue().at(1) == reqShape)  ruleSouth++;
        if(ruleSouth == 0) isValid = false;
    }
    while(currentTile != NULL && (currentRow+1) <= (BOARD_LENGTH-1)) {
        currentTile = board[currentRow+1][destinationColumn];
        if(tile.getValue().compare(currentTile->getValue()) == 0) isValid = false;
        currentRow++;
    }
    // if both exist, determine if the same rule
    if(!emptyNorth && !emptySouth) {
        currentRow = destinationRow;
        comparatorRow = destinationRow;
        if(ruleNorth != ruleSouth) isValid = false;
        // determine if any tiles in south exist in north
        while(comparatorTile != NULL && (comparatorRow-1) >= 0) {
            comparatorTile = board[comparatorRow-1][destinationColumn];
            while(currentTile != NULL && (currentRow+1) <= (BOARD_LENGTH-1)) {
                currentTile = board[currentRow+1][destinationColumn];
                if(comparatorTile->getValue().compare(currentTile->getValue()) == 0) isValid = false;
                currentRow++;
            }
            comparatorRow--;
        }
    }

    // check east
    if(!emptyEast) {
        currentColumn = destinationColumn;
        currentTile = board[destinationRow][currentColumn+1];
        if(currentTile->getValue().at(0) == reqColour) ruleEast--;
        if(currentTile->getValue().at(1) == reqShape)  ruleEast++;
        if(ruleEast == 0) isValid = false;
    }
    while(currentTile != NULL && (currentColumn+1) <= BOARD_LENGTH) {
        currentTile = board[destinationRow][currentColumn+1];
        if(tile.getValue().compare(currentTile->getValue()) == 0) isValid = false;
        currentColumn++;
    }
    // check west
    if(!emptyWest) {
        currentColumn = destinationColumn;
        currentTile = board[destinationRow][currentColumn-1];
        if(currentTile->getValue().at(0) == reqColour) ruleWest--;
        if(currentTile->getValue().at(1) == reqShape)  ruleWest++;
        if(ruleWest == 0) isValid = false;
    }
    while(currentTile != NULL && (currentColumn-1) >= 0) {
        currentTile = board[destinationRow][currentColumn-1];
        if(tile.getValue().compare(currentTile->getValue()) == 0) isValid = false;
        currentColumn--;
    }
    // if both exist, determine if the same rule
    if(!emptyEast && !emptyWest) {
        currentColumn = destinationColumn;
        comparatorColumn = destinationColumn;
        if(ruleEast != ruleWest) isValid = false;
        // determine if any tiles in east exist in west
        while(comparatorTile != NULL && (comparatorColumn+1) <= (BOARD_LENGTH-1)) {
            comparatorTile = board[destinationRow][comparatorColumn+1];
            while(currentTile != NULL && (currentColumn-1) >= 0 ) {
                currentTile = board[destinationRow][currentColumn-1];
                if(comparatorTile->getValue().compare(currentTile->getValue()) == 0) isValid = false;
                currentColumn--;
            }
            comparatorColumn++;
        }
    }

    if(isValid) board[destinationRow][destinationColumn] = tile;
    if(isValid) updateDynamicBoard(destinationRow, destinationColumn);
    return isValid;
}

void GameEngine::saveGame(std::string fileName){
  std::ofstream outFile;
  outFile.open(fileName);

  //loop to print players and deets to file
  //prints max 4 players but not necissarily needs to be 4
  for (int i = 0; i < totalPlayers; i++){
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
    //increment to next player
    currentPlayer++;
    if (currentPlayer==totalPlayers) currentPlayer = 0;

    //end game if tileBag is empty
    if (tileBag.size() == 0){
      inGame = false;

      //loops through all players printing their deets and finding the winner
      std::string winner = "";
      int winningScore = 0;
      for (int i = 0; i < totalPlayers; i++){
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
    board= dynamicBoard;
    std::string boardStr = "";
    String initial = "   ";
    if(colLength>10){
        initial= "  ";
    }
    boardStr = initial;
    String prefix= " ";
    String postfix= " ";
    for(int k=0;k<colLength;k++) {
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
    for (int i = 0; i < rowLength; i++) {
        boardStr += "\n";
        boardStr += alfa;
        boardStr += " |";
        for (int j = 0; j < colLength; j++) {
            String value = "  ";
            if (board[i][j]!=nullptr) {
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
  for (int i = 0; i < totalPlayers; i++){
    for (int x = 0; x < 6; x++){
      Tile* tile = tileBag.get(0);
      playerList[i]->addTile(tile);
      tileBag.deleteTile(*tile);
    }
  }
  // std::cout << playerList[0]->handToString() << std::endl;
}

void GameEngine::updateDynamicBoard(int row, int col) {
    bool rowExpand= false;
    bool colExpand= false;
    int newRowLength= rowLength;
    int newColLength= colLength;
    bool colShift= false;
    bool rowShift= false;

    if (row==0) {
        rowExpand= true;
        rowShift= true;
        newRowLength++;
    }
    else if(row==rowLength-1) {
        rowExpand = true;
        newRowLength++;
    }
    if(col==0) {
        colExpand = true;
        colShift = true;
        newColLength++;
    }
    else if(col==colLength-1) {
        colExpand = true;
        newColLength++;
    }

    if(rowExpand || colExpand) {
        Board *newBoard = new Board[newRowLength];
        for (int i = 0; i < newRowLength; i++) {
            newBoard[i] = new BoardRow[newColLength];
        }

        for (int i = 0; i < rowLength; i++) {
            int newRow = i;
            if (rowShift) {
                newRow++;
                for (int j = 0; j < colLength; j++) {
                    if (dynamicBoard[i][j] != nullptr) {
                        int newCol = j;
                        if (colShift) {
                            newCol++;
                        }
                        newBoard[newRow][newCol] = dynamicBoard[i][j];
                    }
                }
            }
            delete dynamicBoard[i];
        }
        delete dynamicBoard;
        dynamicBoard= newBoard;
    }
}
