
#include "LinkedList.h"
#include "TileCodes.h"
#include "GameEngine.h"

#include "fstream"
#include <iostream>

#define EXIT_SUCCESS      0
#define NUMBER_OF_PLAYERS 2

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

  //array for all player names
  std::string playerList[NUMBER_OF_PLAYERS];

  //loop to prompt for players to however many players are playing
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
    playerList[i] = promptForPlayer(i+1);
  }

  //TODO implement the creation of the game using the array of players

  std::cout << std::endl;
  new GameEngine();
}

//loads game from a given file name
void loadGame(){
  std::cout
  << "Enter the filename from which to load the game" << std::endl
  << "> ";

  //gets filename from input
  std::string fileName = "";
  std::cin >> fileName;

  //attempts to open file
  std::ifstream inFile;
  inFile.open(fileName);

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
  }

  // check all player deets
  int currentLine = 0;
  std::string line = lines[currentLine];
  bool validate = true;
  bool playersRead = false;
  while (playersRead == false){
    if (checkStringCharBetween(line, 'A', 'Z') == false)
      validate = false;
    currentLine++;
    line = lines[currentLine];

    if (checkStringCharBetween(line, '1', '9') == false)
      validate = false;
    currentLine++;
    line = lines[currentLine];

    bool handRead = false;
    int handLength = line.length();
    int c = 0;
    while (handRead == false){
      std::string tile = line.substr(c, 2);
      if (checkValidTile(tile) == false) validate = false;
      c += 2;
      if (c >= handLength) handRead = true;
      c++;
    }
    currentLine++;
    line = lines[currentLine];

    if (line.at(0) == ' ') playersRead = true;
  }

  //check board
  currentLine += 2;
  line = lines[currentLine];
  bool boardRead = false;
  while (boardRead == false){
    bool rowRead = false;
    int c = 3;
    int rowLength = line.length();
    while (rowRead == false && c < rowLength){
      std::string tile = line.substr(c, 2);
      if (checkValidTile(tile) == false && tile != "  ") validate = false;
      c += 3;
      if (c >= rowLength) rowRead = true;
    }

    currentLine++;
    line = lines[currentLine];
    if (line.at(1) != ' ') boardRead = true;
  }

  //check bag
  bool bagRead = false;
  int c = 0;
  int bagLength = line.length();
  while (bagRead == false){
    std::string tile = line.substr(c, 2);
    if (checkValidTile(tile) == false) validate = false;
    c += 2;
    if (c >= bagLength) bagRead = true;
    c++;
  }
  currentLine++;
  line = lines[currentLine];

  if (checkStringCharBetween(line, 'A', 'Z') == false)
    validate = false;
  //check all pieces in hand and bag is correct amount
  std::cout << validate << std::endl;
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
  std::cout
                                                              << std::endl
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
