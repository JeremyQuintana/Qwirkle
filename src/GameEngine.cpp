//
// Created by ariacelesta on 08/05/19.
//

#include "GameEngine.h"

#define BOARD_LENGTH boardLength
#define DEFAULT_BOARD_LENGTH 3

using std::cin;
using std::stoi;

//constructor for a new game
GameEngine::GameEngine(std::string playerListNames[], int totalPlayers) {
    turn= 0;
    inGame= true;
    playerList = new Player*[totalPlayers];
    currentPlayer= 0;
    this->totalPlayers= totalPlayers;

    //creates new players which are added to the playerlist
    for (int i = 0; i < totalPlayers; i++)
      playerList[i] = new Player(playerListNames[i], new LinkedList);
    rowLength= DEFAULT_BOARD_LENGTH;
    colLength= DEFAULT_BOARD_LENGTH;

    assembleDynamicBoard();
    dealTiles();
    startGame();
}

GameEngine::GameEngine(int totalPlayers, int rowLength, int colLength, String playerNames[],
                       int playerScores[], String playerHands[], String board[], String bag, int turn){
    std::cout << "Game  successfully loaded" << std::endl;
    this->currentPlayer= turn;
    inGame= true;
    playerList = new Player*[totalPlayers];
    this->totalPlayers= totalPlayers;
    this->colLength= colLength;
    this->rowLength= rowLength;

    for (int i = 0; i < totalPlayers; i++) {
        String hands[(playerHands[i].length()+1)/3];
        int index= 0;
        playerList[i] = new Player(playerNames[i], new LinkedList);
        playerList[i]->addScore(playerScores[i]);
        for(unsigned int j=0;j<playerHands[i].length();j+=3){
            hands[index]= playerHands[i].substr(j,2);
            index++;
        }
        for(String hand:hands){
            playerList[i]->addTile(new Tile(hand));
        }
    }

    String bags[(bag.length()+1)/3];
    int index= 0;
    for(unsigned int i=0;i<bag.length();i+=3){
        bags[index]= bag.substr(i,2);
        index++;
    }
    for(String bagTile:bags){
        tileBag.addBack(new Tile(bagTile));
    }

    assembleDynamicBoard();

    for(int i=0;i<rowLength;i++){
        String row[colLength];
        index= 0;
        for(unsigned int j=0;j<board[i].length();j+=3){
            row[index]= board[i].substr(j,2);
            index++;
        }
        for(int k=0;k<colLength;k++){
            if(!(row[k].compare("  ")==0)){
                dynamicBoard[i][k]= new Tile(row[k]);
            }
        }
    }
    startGame();
}

//main function that runs the actual game
void GameEngine::startGame() {
    std::cin.clear();
    std::cin.ignore();
    //loops while there is no winner yet and game is still running
    std::cin.clear();
    std::cin.ignore();
    inGame = true;
    //loops while the game is not ended
    while(inGame){
      //prints current players name
      std::cout << std::endl
      << playerList[currentPlayer]->getName()
      << ", it's your turn" << std::endl;
      //loops through each player and prints their scores
      for (int i = 0; i < totalPlayers; i++){
        std::cout
        << "Score for " << playerList[i]->getName()
        << ": " << playerList[i]->getScore() << std::endl;

      }
      //prints the board
      std::cout << printBoard() << std::endl;
      //prints the hand of the current player
      std::cout
      << "Your hand is:"                           << std::endl
      << playerList[currentPlayer]->handToString() << std::endl << std::endl;

      //takes the turn
      bool endGame = takeTurn();
      //if the ^D was not used then endGame stays true and the endTurn runs
      if (endGame == false) endTurn();
      else inGame = false;
      // inGame = false;
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
}

//creates a board of default size
void GameEngine::assembleDynamicBoard(){
    dynamicBoard= new Board[rowLength];
    for (int i=0;i<rowLength;i++){
        dynamicBoard[i]= new BoardRow[colLength];
    }
}

//take turn function that decides what the player wants to do with their turn
bool GameEngine::takeTurn() {
    bool endGame = false;
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
        //if ^D then it exits the turn and the game
        else if(std::cin.eof()) {
          endGame = true;
          validated = true;
        }
        else std::cout << "Error - Invalid option" << std::endl;

        //calls relevant functions and if unsuccesful stays in loop
        if(option == 1) {
          Tile tile = Tile(playerCommand.at(6), playerCommand.at(7) - '0');
          if (placeTile(tile, playerCommand.substr(12,
            playerCommand.length()-12))) validated = true;
        } else if(option == 2) {
          Tile tile = Tile(playerCommand.at(8), playerCommand.at(9) - '0');
          if (replaceTile(tile)) validated = true;;
        } else if(option == 3) {
          saveGame(playerCommand.substr(5, playerCommand.length()-5));
        }
        option = 0;
    }

    return endGame;
}

//function if the player decides to place a tile for their turns
bool GameEngine::placeTile(Tile tile, std::string coordinate) {
    bool isValid = true;
    // row player asked for
    char row = coordinate.at(0);
    int destinationRow = 0;
    //check for 
    if (row >= 'A' && row <= 'Z') destinationRow = row - 65;
    else {
      std::cout << "Error - Invalid row coordinate" << std::endl;
      isValid = false;
    }
    // column player asked for
    std::string column = coordinate.substr(1, coordinate.length()-1);
    int columnLength = column.length();
    for (int i = 0; i < columnLength && isValid == true; i++){
      if (column.at(i) < '0' || column.at(i) > '9'){
        isValid = false;
        std::cout << "Error - Invalid column coordinate" << std::endl;
      }
    }
    int destinationColumn = 0;
    if(isValid == true) destinationColumn = std::stoi(column);
    // copies of these to use as counters
    int currentRow = destinationRow;
    int currentColumn = destinationColumn;
    int comparatorRow = destinationRow;
    int comparatorColumn = destinationColumn;
    Tile* currentTile = nullptr;
    Tile* comparatorTile = nullptr;
    // bool values used for checks and rule variables -> -1 is colour, 1 is shape
    bool emptyNorth = false, emptySouth = false, emptyEast = false, emptyWest = false;
    int ruleNorth = 0, ruleSouth = 0, ruleEast = 0, ruleWest = 0;
    // required colour and/or shape
    char reqColour = tile.getValue().at(0);
    char reqShape = tile.getValue().at(1);
    // counter for points earned
    int rowScore = 0, colScore = 0;

    if (playerList[currentPlayer]->getTilePtr(tile) == nullptr) {
      std::cout << "Error - Tile not found" << std::endl;
      isValid = false;
    }
    // check coordinate exists - needs to be changed for dynamic boards in future
    if(destinationRow < 0 || destinationRow > rowLength || destinationColumn < 0 || destinationColumn > colLength) isValid = false;
    // check coordinate is not currently occupied
    if(board[destinationRow][destinationColumn]!= NULL) isValid = false;
    // check tile is placed adjacent to an existing tile after turn 1
    // assuming turn denotes turns passed
    emptyNorth = (destinationRow <= 0 || board[destinationRow-1][destinationColumn] == NULL) ? true : false;
    emptySouth = (destinationRow >= rowLength-1 || board[destinationRow+1][destinationColumn] == NULL) ? true : false;
    emptyEast = (destinationColumn >= colLength-1 || board[destinationRow][destinationColumn+1] == NULL) ? true : false;
    emptyWest = (destinationColumn <= 0 || board[destinationRow][destinationColumn-1] == NULL) ? true : false;
    if(turn >= 1 && emptyNorth && emptySouth && emptyEast && emptyWest){
      isValid = false;
      std::cout << "Error - No surrounding tiles" << std::endl;
    }

    // check north
    if(!emptyNorth && isValid == true) {
        currentRow = destinationRow;
        currentTile = board[currentRow-1][destinationColumn];
        if(currentTile->getValue().at(0) == reqColour) ruleNorth--;
        if(currentTile->getValue().at(1) == reqShape)  ruleNorth++;
        if(ruleNorth == 0) isValid = false;
        rowScore++;
        while((currentRow-1) >= 0 && board[currentRow-1][destinationColumn] != NULL) {
            currentTile = board[currentRow-1][destinationColumn];
            if(ruleNorth == 1 && currentTile->getValue().at(1) != reqShape) isValid = false;
            if(ruleNorth == -1 && currentTile->getValue().at(0) != reqColour) isValid = false;
            else rowScore++;
            currentRow--;
        }
        std::cout << "Error - Invalid tile placement" << std::endl;
    }

    // check south
    if(!emptySouth && isValid == true) {
        currentRow = destinationRow;
        currentTile = board[currentRow+1][destinationColumn];
        if(currentTile->getValue().at(0) == reqColour) ruleSouth--;
        if(currentTile->getValue().at(1) == reqShape)  ruleSouth++;
        if(ruleSouth == 0) isValid = false;
        rowScore++;;
        while((currentRow+1) <= rowLength && board[currentRow+1][destinationColumn] != NULL) {
            currentTile = board[currentRow+1][destinationColumn];
            if(ruleSouth == 1 && currentTile->getValue().at(1) != reqShape) isValid = false;
            if(ruleSouth == -1 && currentTile->getValue().at(0) != reqColour) isValid = false;
            else rowScore++;
            currentRow++;
        }
        std::cout << "Error - Invalid tile placement" << std::endl;
    }
    // if both exist, determine if the same rule
    if(!emptyNorth && !emptySouth && isValid == true) {
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
    if (isValid == true && rowScore == 6) std::cout << std::endl << "QWIRKLE!!!" << std::endl;

    // check east
    if(!emptyEast && isValid == true) {
        currentColumn = destinationColumn;
        currentTile = board[destinationRow][currentColumn+1];
        if(currentTile->getValue().at(0) == reqColour) ruleEast--;
        if(currentTile->getValue().at(1) == reqShape)  ruleEast++;
        if(ruleEast == 0) isValid = false;
        colScore++;
        while((currentColumn+1) <= colLength && board[destinationRow][currentColumn+1] != NULL) {
            currentTile = board[destinationRow][currentColumn+1];
            if(ruleEast == 1 && currentTile->getValue().at(1) != reqShape) isValid = false;
            if(ruleEast == -1 && currentTile->getValue().at(0) != reqColour) isValid = false;
            else colScore++;
            currentColumn++;
        }
        std::cout << "Error - Invalid tile placement" << std::endl;
    }
    // check west
    if(!emptyWest && isValid == true) {
        currentColumn = destinationColumn;
        currentTile = board[destinationRow][currentColumn-1];
        if(currentTile->getValue().at(0) == reqColour) ruleWest--;
        if(currentTile->getValue().at(1) == reqShape)  ruleWest++;
        if(ruleWest == 0) isValid = false;
        colScore++;
        while((currentColumn-1) >= 0 && board[destinationRow][currentColumn-1] != NULL) {
            currentTile = board[destinationRow][currentColumn-1];
            if(ruleWest == 1 && currentTile->getValue().at(1) != reqShape) isValid = false;
            if(ruleWest == -1 && currentTile->getValue().at(0) != reqColour) isValid = false;
            else colScore++;
            currentColumn--;
        }
        std::cout << "Error - Invalid tile placement" << std::endl;
    }
    // if both exist, determine if the same rule
    if(!emptyEast && !emptyWest && isValid == true) {
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
    if (isValid == true && colScore == 6) std::cout << std::endl << "QWIRKLE!!!" << std::endl;

    if(isValid){
      board[destinationRow][destinationColumn] = playerList[currentPlayer]->getTilePtr(tile);
      updateDynamicBoard(destinationRow, destinationColumn);
      playerList[currentPlayer]->addScore(colScore+rowScore);
      // std::cout << playerList[currentPlayer]->handToString() << std::endl;
      Tile* tileToAdd = tileBag.get(0);
            // std::cout << playerList[currentPlayer]->handToString() << std::endl;
      playerList[currentPlayer]->addTile(tileToAdd);
      tileBag.deleteTile(*tileToAdd);
      playerList[currentPlayer]->removeTile(tile);
      turn++;
    }
    return isValid;
}

void GameEngine::saveGame(std::string fileName){
  std::ofstream outFile ("../src/"+fileName);

  outFile << totalPlayers << endl;
  outFile << rowLength << endl;
  outFile << colLength << endl;

  //loop to print players and deets to file
  //prints max 4 players but not necissarily needs to be 4
  for (int i = 0; i < totalPlayers; i++){
    outFile
      << playerList[i]->getName()      << endl
      << playerList[i]->getScore()     << endl
      << playerList[i]->handToString() << endl;
  }

  outFile << boardToString() << endl;
  outFile << tileBag.listToString() << endl;
  outFile << currentPlayer << endl;

  outFile.close();
  std::cout << std::endl << "Game successfully saved" << std::endl;
}

bool GameEngine::replaceTile(Tile tile) {
    bool successful = false;
    Tile* toReplace = playerList[currentPlayer]->getTilePtr(tile);
    if (toReplace != nullptr){
      Tile* tileToAdd = tileBag.get(0);
      playerList[currentPlayer]->addTile(tileToAdd);
      tileBag.deleteTile(*tileToAdd);
      tileBag.addFront(toReplace);
      playerList[currentPlayer]->removeTile(tile);
      tileBag.shuffle();
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
        std::cout << "Game over" << std::endl;
        //prints player deets
        std::cout << "Score for " << playerList[i]->getName()
        << ": " << playerList[i]->getScore() << std::endl;

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
      std::cout << "Player " << winner << " won!" << std::endl;
    }
    //TODO check if theres valid moves
}

//prints the entire board to the system console including the tiles placed
std::string GameEngine::printBoard() {
    board = dynamicBoard;
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
    return boardStr;
}

String GameEngine::boardToString() {
    String stringBoard;
    String tile;
    for(int i=0;i<rowLength;i++){
        for(int j=0;j<colLength;j++){
            if(dynamicBoard[i][j]==nullptr){
                tile= "  ";
            }
            else {
                tile= dynamicBoard[i][j]->getValue();
            }
            stringBoard+=tile+"|";
        }
        stringBoard += "\n";
    }
    return stringBoard;
}

void GameEngine::dealTiles(){
  //create tileBag
  Colour tileColours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
  Shape tileShapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

  for (Colour colour : tileColours){
    for (Shape shape : tileShapes){
      int copies = 1;
      for (int i = 0; i < copies; i++){
        Tile* tile = new Tile(colour, shape);
        tileBag.addFront(tile);
      }
    }
  }

  tileBag.shuffle();

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
            for (int j = 0; j < newColLength; j++){
              newBoard[i][j] = nullptr;
            }
        }

        for (int col = 0; col < colLength; col++){
          for (int row = 0; row < rowLength; row++){
            newBoard[row+rowShift][col+colShift] = dynamicBoard[row][col];
          }
        }
        delete[] dynamicBoard;
        dynamicBoard= newBoard;
        rowLength = newRowLength;
        colLength = newColLength;
    }
}

GameEngine::~GameEngine(){
  delete[] board;
  for (int i = 0; i < colLength; i++){
    delete[] dynamicBoard[i];
  }
  delete[] dynamicBoard;
  delete[] playerList;
}
