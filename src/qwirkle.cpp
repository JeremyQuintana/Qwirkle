
#include "LinkedList.h"
#include "Player.h"
#include "TileCodes.h"
#include "GameEngine.h"

#include "fstream"
#include <iostream>

#define EXIT_SUCCESS      0
#define NUMBER_OF_PLAYERS 4

typedef std::string String;

void newGame();
void loadGame();
void showStudentInformation();
int menuOptions();
std::string promptForPlayer(int playerNumber);
bool checkStringCharBetween(std::string str, char min, char max);
bool checkValidTile(std::string tile);

int main(void) {
  std::cout

  << "Welcome to Qwirkle!"           << std::endl
  << "-------------------"           << std::endl;
  int option = 0;

  while (option != 4){
    option = menuOptions();

    if (option == 1) newGame();
    if (option == 2) loadGame();
    if (option == 3) showStudentInformation();
  }

  std::cout << "Goodbye" << std::endl;

  return EXIT_SUCCESS;
}

//starts a new game
void newGame(){
  std::cout << "Starting a New Game" << std::endl;

  bool validate = false;
  int amountOfPlayers = 0;
  while (validate == false){
    std::cout << std::endl
    << "Enter amount of players:" << std::endl
    << "> ";
    std::string input = "";
    std::cin >> input;

    if (checkStringCharBetween(input, '2', '4') == true
        && input.length() == 1) {
          validate = true;
          amountOfPlayers = input.at(0) - '0';
    }
    else std::cout << "Error - Amount must be between 1 and 5" << std::endl;
  }

  //array for all player names
  std::string playerList[amountOfPlayers];

  //loop to prompt for players to however many players are playing
  for (int i = 0; i < amountOfPlayers; i++){
    playerList[i] = promptForPlayer(i+1);
  }

  //TODO implement the creation of the game using the array of players

  std::cout << std::endl;
  new GameEngine(playerList, amountOfPlayers);
}

//loads game from a given file name
void loadGame(){
  std::cout
  << "Enter the filename from which to load the game" << std::endl
  << "> ";

  //gets filename from input
  String input;
  std::cin >> input;

  //attempts to open file
  std::ifstream inFile(input);

  //reads from file if it can and stores it line by line, in lines array
  std::string lines[500];
  int lineNumber = 0;
  if(!inFile){
    std::cout << "Error - Can not open or find file" << std::endl;
  } else{
    while (!inFile.eof()){
      std::getline(inFile, lines[lineNumber]);
      lineNumber++;
    }
      int currentLine = 0;
      int playerNum= std::stoi(lines[currentLine]);
      currentLine++;
      int initRowLength= std::stoi(lines[currentLine]);
      currentLine++;
      int initColLength= std::stoi(lines[currentLine]);
      currentLine++;

      // check all player deets
      std::string line;
      bool isWrongFormat = false;
      String tempName;
      String tempScore;
      String tempHand;
      String playerNames[playerNum];
      int playerScores[playerNum];
      String playerHands[playerNum];

      for(int i=0;i<playerNum;i++){
          tempName= lines[currentLine];
          currentLine++;
          tempScore= lines[currentLine];
          if (checkStringCharBetween(tempName, 'A', 'Z') == false ||
              checkStringCharBetween(line, '1', '9') == false) {
              isWrongFormat = true;
          }
          currentLine++;
          tempHand = lines[currentLine];

          int handLength = tempHand.length();
          int index = 0;
          while (index-1 < handLength){
              String tile = line.substr(index, 2);
              if (checkValidTile(tile) == false) {
                  isWrongFormat = true;
              }
              index += 3;
          }
          playerNames[i]= tempName;
          playerScores[i]= std::stoi(tempScore);
          playerHands[i]= tempHand;
          currentLine++;
      }

      String board[initRowLength];

      //check board
      for(int i=0;i<initRowLength;i++){
          line = lines[currentLine];
          board[i]= line;
          currentLine++;
          /*bool rowRead = false;
        int c = 3;
        int rowLength = line.length();
        while (rowRead == false && c < rowLength){
          std::string tile = line.substr(c, 2);
          if (checkValidTile(tile) == false && tile != "  "){
              isValidated = false;
          }
          c += 3;
          if (c >= rowLength) rowRead = true;
        }

        currentLine++;
        line = lines[currentLine];
        if (line.at(1) != ' ') boardRead = true;*/
      }

      //check bag
      String bag= lines[currentLine];
      int c = 0;
      int bagLength = bag.length();
      while (c-1<bagLength){
          std::string tile = line.substr(c, 2);
          if (checkValidTile(tile) == false) {
              isWrongFormat = true;
          }
          c += 3;
      }
      currentLine++;
      String turnString = lines[currentLine];

      if (checkStringCharBetween(turnString, '1', '9') == false) {
          isWrongFormat = true;
      }
      int turn= std::stoi(turnString);
      //check all pieces in hand and bag is correct amount

      if(isWrongFormat){
          std::cout << "Save Data Invalid Format." << std::endl;
      }
      else{
          new GameEngine(playerNum, initRowLength, initColLength, playerNames,
                         playerScores, playerHands, board, bag, turn);
      }
  }


  std::cout << std::endl;
}

//shows student student information for team
void showStudentInformation(){
  std::cout
  << "-----------------------------------" << std::endl
  << "Name: Edward Kahiro Kuo"             << std::endl
  << "Student ID: s3691466"                << std::endl
  << "Email: s3691466@student.rmit.edu.au" << std::endl
                                           << std::endl
  << "Name: Justin Seymour"                << std::endl
  << "Student ID: s3655931"                << std::endl
  << "Email: s3655931@student.rmit.edu.au" << std::endl
                                           << std::endl
  << "Name: Jeremy Quintana"               << std::endl
  << "Student ID: s3719476"                << std::endl
  << "Email: s3719476@student.rmit.edu.au" << std::endl
                                           << std::endl
  << "Name: Luke Di Guglielmo"             << std::endl
  << "Student ID: s3724928"                << std::endl
  << "Email: s3724928@student.rmit.edu.au" << std::endl
  << "-----------------------------------" << std::endl;

  std::cout << std::endl;
}

//prints the menu options and returns valid option
int menuOptions(){
  std::cout
  << "Menu"                          << std::endl
  << "----"                          << std::endl
  << "1. New Game"                   << std::endl
  << "2. Load Game"                  << std::endl
  << "3. Show Student Information"   << std::endl
  << "4. Quit"                       << std::endl
                                     << std::endl
  << "> ";
  //validate input from user
  int option = 0;
  bool validated = false;
  while (validated == false){
    std::cin >> option;
    if (option == 1 || option == 2 || option == 3 || option == 4)
      validated = true;
    else std::cout << "Error - Invalid option" << std::endl << "> ";
    std::cin.clear();
    std::cin.ignore();
  }
  std::cout << std::endl;

  return option;
}

//prompts for player and returns a player name
std::string promptForPlayer(int playerNumber){
  std::string player = "";
  std::cout << std::endl
  << "Enter a name for player " << playerNumber
  <<                           " (uppercase characters only)" << std::endl
  << "> ";

  //loop until name input is correct
  bool validate = false;
  while (validate == false){
    std::cin >> player;

    //check input is all upper case letters
    validate = checkStringCharBetween(player, 'A', 'Z');

    //prints error message if incorrect
    if (validate == false)
      std::cout << "Invalid input" << std::endl << "> ";
  }

  return player;
}

bool checkStringCharBetween(std::string str, char min, char max){
  bool validate = true;
  for (int i = 0; str[i] != '\0'; i++){
    if (str.at(i) < min || str.at(i) > max) validate = false;
  }
  return validate;
}

bool checkValidTile(std::string tile){
  bool validColour = false;
  bool validShape = false;
  if (tile.length() == 2){
    char colour = tile.at(0);
    int shape = tile.at(1) - '0';
    if (
      colour == RED     ||
      colour == ORANGE  ||
      colour == YELLOW  ||
      colour == GREEN   ||
      colour == BLUE    ||
      colour == PURPLE
    ) validColour = true;
    if (
      shape == CIRCLE   ||
      shape == STAR_4   ||
      shape == DIAMOND  ||
      shape == SQUARE   ||
      shape == STAR_6   ||
      shape == CLOVER
    ) validShape = true;
  }

  bool valid = false;
  if (validColour == true && validShape == true) valid = true;

  return valid;
}
