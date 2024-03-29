
#include "GameEngine.h"

#define BOARD_LENGTH boardLength
#define DEFAULT_BOARD_LENGTH 3
#define TILE_FORMAT_DISTANCE 3
#define TILE_STRING_LENGTH 2
#define COPY_OF_TILES 2
#define SAVE_COMMAND_LENGTH 5
#define REPLACE_COMMAND_LENGTH 8
#define PLACE_COMMAND_LENGTH 6
#define PLACE_AT_COMMAND_START_LENGTH 8
#define PLACE_AT_COMMAND_END_LENGTH 4
#define HELP_COMMAND_LENGTH 4
#define OPTION_SAVE 3
#define OPTION_REPLACE 2
#define OPTION_PLACE 1

using std::cin;
using std::stoi;

//a constructor for a new GameEngine for a new game
GameEngine::GameEngine(std::string playerListNames[], int totalPlayers) {
    turn= 0;
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

//constructor for a new GameEngine based on a save file after a load
GameEngine::GameEngine(int totalPlayers, int rowLength, int colLength,
                        String playerNames[], int playerScores[],
                        String playerHands[], String board[],
                        String bag, int turnCount, int currentPlayer){
    std::cout << "Game  successfully loaded" << std::endl;
    this->currentPlayer= currentPlayer;
    this->turn= turnCount;
    playerList = new Player*[totalPlayers];
    this->totalPlayers= totalPlayers;
    this->colLength= colLength;
    this->rowLength= rowLength;

    //loops through the players array and generate new players
    for (int i = 0; i < totalPlayers; i++) {
        //the total number of cards, after taking into account the formatting
        //of each string line in the savefile
        String hands[(playerHands[i].length()+1)/TILE_FORMAT_DISTANCE];
        int index= 0;
        playerList[i] = new Player(playerNames[i], new LinkedList);
        playerList[i]->addScore(playerScores[i]);
        //processes each tile in the string and puts into the hand array
        for(unsigned int j=0;j<playerHands[i].length();j+=TILE_FORMAT_DISTANCE){
            hands[index]= playerHands[i].substr(j,TILE_STRING_LENGTH);
            index++;
        }
        //adds each hand in the hand array as Tiles into each player
        for(String hand:hands){
            playerList[i]->addTile(new Tile(hand));
        }
    }

    //the total number of tiles in the bag after taking into account the string
    //formatting in the savefile
    String bags[(bag.length()+1)/TILE_FORMAT_DISTANCE];
    int index= 0;
    //processes each tile in the string and put them inside the bag array
    for(unsigned int i=0;i<bag.length();i+=TILE_FORMAT_DISTANCE){
        bags[index]= bag.substr(i,TILE_STRING_LENGTH);
        index++;
    }
    //adds each tile into the bag linkedlist as a new tile
    for(String bagTile:bags){
        tileBag.addBack(new Tile(bagTile));
    }

    assembleDynamicBoard();

    //processes the tiles on the dynamicBoard from the dynamicBoard string array and puts them
    //inside the dynamic dynamicBoard
    for(int i=0;i<rowLength;i++){
        String row[colLength];
        index= 0;
        for(unsigned int j=0;j<board[i].length();j+=TILE_FORMAT_DISTANCE){
            row[index]= board[i].substr(j,TILE_STRING_LENGTH);
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
      //prints the dynamicBoard
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

//creates a dynamicBoard of the size rowLength and colLength, with the default value of 3x3
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
        if(playerCommand.substr(0,SAVE_COMMAND_LENGTH).compare("save ") == 0)
                                                        option = OPTION_SAVE;
        else if(playerCommand.substr(0,REPLACE_COMMAND_LENGTH)
                             .compare("replace ") == 0)
                                                        option = OPTION_REPLACE;
        else if(playerCommand.substr(0,PLACE_COMMAND_LENGTH)
                             .compare("place ") == 0
                && playerCommand.substr
                   (PLACE_AT_COMMAND_START_LENGTH, PLACE_AT_COMMAND_END_LENGTH)
                             .compare(" at ") == 0)
                                                        option = OPTION_PLACE;
        //if ^D then it exits the turn and the game
        else if(std::cin.eof()) {
          endGame = true;
          validated = true;
        }
        else if(playerCommand.substr(0,HELP_COMMAND_LENGTH).compare("help") == 0) {
            std::cout << "Commands" << std::endl;
            std::cout << "=========" << std::endl;

            std::cout << "To place tile from hand to location on dynamicBoard, type:"
                << std::endl;
            std::cout << "place <tile code> at <location code>" << std::endl;
            std::cout << "\teg. place R1 at B2" << std::endl << std::endl;

            std::cout << "To replace a tile in hand with new one, type: "
                << std::endl;
            std::cout << "replace <tile code>" << std::endl;
            std::cout << "\teg. replace Y3" << std::endl << std::endl;

            std::cout << "To save the current game, type: " << std::endl;
            std::cout << "save <name of file>" << std::endl;
            std::cout << "\teg. save examplefile" << std::endl;
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

    char row = 0;
    std::string column = "";
    int destinationRow = 0;
    int destinationColumn = 0;

    if (coordinate.length() > 1){
      bool validRow = true;
      row = coordinate.at(0);
      //check for row
      if (row >= 'A' && row <= 'Z') destinationRow = row - 65;
      else validRow = false;
      if (!validRow){
        std::cout << "Error - Invalid row coordinate" << std::endl;
        isValid = false;
      }
      // column player asked for
      column = coordinate.substr(1, coordinate.length()-1);
      int columnLength = column.length();
      bool validCol = true;
      if (column == "") validCol = false;
      for (int i = 0; i < columnLength && isValid == true; i++){
        if (column.at(i) < '0' || column.at(i) > '9') validCol = false;
      }
      if (!validCol){
        isValid = false;
        std::cout << "Error - Invalid column coordinate" << std::endl;
      }
      if(isValid == true) destinationColumn = std::stoi(column);
    } else {
      isValid  = false;
      std::cout << "Error - No coordinate" << std::endl;
    }
    // copies of these to use as counters
    int currentRow = destinationRow;
    int currentColumn = destinationColumn;
    int comparatorRow = destinationRow;
    int comparatorColumn = destinationColumn;
    Tile* currentTile = nullptr;
    Tile* comparatorTile = nullptr;
    //bool values used for checks and rule variables -> -1 is colour, 1 is shape
    bool emptyNorth = false, emptySouth = false,
         emptyEast = false, emptyWest = false;
    int ruleNorth = 0, ruleSouth = 0, ruleEast = 0, ruleWest = 0;
    // required colour and/or shape
    char reqColour = tile.getValue().at(0);
    char reqShape = tile.getValue().at(1);
    // counter for points earned
    int rowScore = 0, colScore = 0;

    //check if tile exists
    if (isValid && playerList[currentPlayer]->getTilePtr(tile) == nullptr) {
      std::cout << "Error - Tile not found" << std::endl;
      isValid = false;
    }
    //check coordinate exists - needs to be changed for dynamic boards in future
    if(isValid && (destinationRow < 0 || destinationRow > rowLength-1
    || destinationColumn < 0 || destinationColumn > colLength-1)){
      std::cout << "Error - Outside of dynamicBoard" << std::endl;
      isValid = false;
    }
    // check coordinate is not currently occupied
    if(isValid &&
      dynamicBoard[destinationRow][destinationColumn]!= NULL) isValid = false;
    // check tile is placed adjacent to an existing tile after turn 1
    // assuming turn denotes turns passed
    emptyNorth = (isValid && (destinationRow <= 0
      || dynamicBoard[destinationRow-1][destinationColumn] == NULL)) ? true : false;
    emptySouth = (isValid && (destinationRow >= rowLength-1
      || dynamicBoard[destinationRow+1][destinationColumn] == NULL)) ? true : false;
    emptyEast = (isValid && (destinationColumn >= colLength-1
      || dynamicBoard[destinationRow][destinationColumn+1] == NULL)) ? true : false;
    emptyWest = (isValid && (destinationColumn <= 0
      || dynamicBoard[destinationRow][destinationColumn-1] == NULL)) ? true : false;
    if(isValid && turn >= 1
       && emptyNorth && emptySouth && emptyEast && emptyWest){
      isValid = false;
      std::cout << "Error - No surrounding tiles" << std::endl;
    }

    // check north
    if(!emptyNorth && isValid == true) {
        currentRow = destinationRow;
        currentTile = dynamicBoard[currentRow-1][destinationColumn];
        if(currentTile->getValue().at(0) == reqColour) ruleNorth--;
        if(currentTile->getValue().at(1) == reqShape)  ruleNorth++;
        if(ruleNorth == 0) isValid = false;
        rowScore++;
        while((currentRow-1) >= 0
        && dynamicBoard[currentRow-1][destinationColumn] != NULL) {
            currentTile = dynamicBoard[currentRow-1][destinationColumn];
            if(tile.getValue().compare(currentTile->getValue()) == 0)
              isValid = false;
            if(ruleNorth == 1 && currentTile->getValue().at(1) != reqShape)
              isValid = false;
            if(ruleNorth == -1 && currentTile->getValue().at(0) != reqColour)
              isValid = false;
            else rowScore++;
            currentRow--;
        }
        if (isValid == false)
          std::cout << "Error - Invalid tile placement" << std::endl;
    }

    // check south
    if(!emptySouth && isValid == true) {
        currentRow = destinationRow;
        currentTile = dynamicBoard[currentRow+1][destinationColumn];
        if(currentTile->getValue().at(0) == reqColour) ruleSouth--;
        if(currentTile->getValue().at(1) == reqShape)  ruleSouth++;
        if(ruleSouth == 0) isValid = false;
        rowScore++;;
        while((currentRow+1) <= rowLength
        && dynamicBoard[currentRow+1][destinationColumn] != NULL) {
            currentTile = dynamicBoard[currentRow+1][destinationColumn];
            if(tile.getValue().compare(currentTile->getValue()) == 0)
              isValid = false;
            if(ruleSouth == 1 && currentTile->getValue().at(1) != reqShape)
              isValid = false;
            if(ruleSouth == -1 && currentTile->getValue().at(0) != reqColour)
              isValid = false;
            else rowScore++;
            currentRow++;
        }
        if (isValid == false)
          std::cout << "Error - Invalid tile placement" << std::endl;
    }
    // if both exist, determine if the same rule
    if(!emptyNorth && !emptySouth && isValid == true) {
        currentRow = destinationRow;
        comparatorRow = destinationRow;
        if(ruleNorth != ruleSouth) isValid = false;
        // determine if any tiles in south exist in north
        while(comparatorTile != NULL && (comparatorRow-1) >= 0) {
            comparatorTile = dynamicBoard[comparatorRow-1][destinationColumn];
            while(currentTile != NULL && (currentRow+1) <= (BOARD_LENGTH-1)) {
                currentTile = dynamicBoard[currentRow+1][destinationColumn];
                if(comparatorTile->getValue()
                .compare(currentTile->getValue()) == 0) isValid = false;
                currentRow++;
            }
            comparatorRow--;
        }
    }
    if (isValid == true && rowScore == 6)
      std::cout << std::endl << "QWIRKLE!!!" << std::endl;

    // check east
    if(!emptyEast && isValid == true) {
        currentColumn = destinationColumn;
        currentTile = dynamicBoard[destinationRow][currentColumn+1];
        if(currentTile->getValue().at(0) == reqColour) ruleEast--;
        if(currentTile->getValue().at(1) == reqShape)  ruleEast++;
        if(ruleEast == 0) isValid = false;
        colScore++;
        while((currentColumn+1) <= colLength
        && dynamicBoard[destinationRow][currentColumn+1] != NULL) {
            currentTile = dynamicBoard[destinationRow][currentColumn+1];
            if(tile.getValue().compare(currentTile->getValue()) == 0)
              isValid = false;
            if(ruleEast == 1 && currentTile->getValue().at(1) != reqShape)
              isValid = false;
            if(ruleEast == -1 && currentTile->getValue().at(0) != reqColour)
              isValid = false;
            else colScore++;
            currentColumn++;
        }
        if (isValid == false)
          std::cout << "Error - Invalid tile placement" << std::endl;
    }
    // check west
    if(!emptyWest && isValid == true) {
        currentColumn = destinationColumn;
        currentTile = dynamicBoard[destinationRow][currentColumn-1];
        if(currentTile->getValue().at(0) == reqColour) ruleWest--;
        if(currentTile->getValue().at(1) == reqShape)  ruleWest++;
        if(ruleWest == 0) isValid = false;
        colScore++;
        while((currentColumn-1) >= 0
        && dynamicBoard[destinationRow][currentColumn-1] != NULL) {
            currentTile = dynamicBoard[destinationRow][currentColumn-1];
            if(tile.getValue().compare(currentTile->getValue()) == 0)
              isValid = false;
            if(ruleWest == 1 && currentTile->getValue().at(1) != reqShape)
              isValid = false;
            if(ruleWest == -1 && currentTile->getValue().at(0) != reqColour)
              isValid = false;
            else colScore++;
            currentColumn--;
        }
        if (isValid == false)
          std::cout << "Error - Invalid tile placement" << std::endl;
    }
    // if both exist, determine if the same rule
    if(!emptyEast && !emptyWest && isValid == true) {
        currentColumn = destinationColumn;
        comparatorColumn = destinationColumn;
        if(ruleEast != ruleWest) isValid = false;
        // determine if any tiles in east exist in west
        while(comparatorTile != NULL
          && (comparatorColumn+1) <= (BOARD_LENGTH-1)) {
            comparatorTile = dynamicBoard[destinationRow][comparatorColumn+1];
            while(currentTile != NULL && (currentColumn-1) >= 0 ) {
                currentTile = dynamicBoard[destinationRow][currentColumn-1];
                if(comparatorTile->getValue()
                .compare(currentTile->getValue()) == 0) isValid = false;
                currentColumn--;
            }
            comparatorColumn++;
        }
    }
    if (isValid == true && colScore == 6)
      std::cout << std::endl << "QWIRKLE!!!" << std::endl;

    //if isValid continue to place the tile and draw
    if(isValid){
      //place tile and update dynamicBoard
      dynamicBoard[destinationRow][destinationColumn] =
      playerList[currentPlayer]->getTilePtr(tile);
      updateDynamicBoard(destinationRow, destinationColumn);
      //remove tile from hand and draw new tile
      if (turn != 0) playerList[currentPlayer]->addScore(colScore+rowScore);
      else playerList[currentPlayer]->addScore(1);
      Tile* tileToAdd = tileBag.get(0);
      playerList[currentPlayer]->addTile(tileToAdd);
      tileBag.deleteTile(*tileToAdd);
      playerList[currentPlayer]->removeTile(tile);
      turn++;
    }
    return isValid;
}

//saves the current game into a savefile
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
  outFile << turn << endl;
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

//prints the entire dynamicBoard to the system console including the tiles placed
std::string GameEngine::printBoard() {
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
            if (dynamicBoard[i][j]!=nullptr) {
              value = dynamicBoard[i][j]->getValue();
            }
            boardStr += value + "|";
        }
        alfa+=1;

    }
    return boardStr;
}

//takes the state of the curent dynamicBoard and turns it into a simple string
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
      int copies = COPY_OF_TILES;
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
}
