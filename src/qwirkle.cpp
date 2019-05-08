
#include "LinkedList.h"

#include "fstream"
#include <iostream>
#include "GameEngine.h"

#define EXIT_SUCCESS      0
#define NUMBER_OF_PLAYERS 2

void newGame();
void loadGame();
void showStudentInformation();
int menuOptions();
std::string promptForPlayer(int playerNumber);
void toUpperCase(std::string& str);

int main(void) {
  int option = 0;

  while (option != 4){
    option = menuOptions();

    if (option == 1) newGame();
    if (option == 2) loadGame();
    if (option == 3) showStudentInformation();
  }

  std::cout << "Goodbye";
  //previous code starter code, not sure what its for
  // LinkedList* list = new LinkedList();
  // delete list;
  //
  // std::cout << "TODO: Implement Qwirkle!" << std::endl;

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
  GameEngine* game= new GameEngine();
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

  //TODO check that file is in correct format
  //check all player deets
  //check board
  //check bag
  //check all pieces in hand and bag is correct amount

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
  << "Welcome to Qwirkle!"           << std::endl
  << "-------------------"           << std::endl
                                     << std::endl
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
  std::cout
                                                              << std::endl
  << "Enter a name for player " << playerNumber
  <<                           " (uppercase characters only)" << std::endl
  << "> ";
  std::string player = "";
  std::cin >> player;
  toUpperCase(player);

  return player;
}

void toUpperCase(std::string& str){
  for (int i = 0; str[i] != '\0'; i++){
    str[i] = toupper(str[i]);
  }
}
