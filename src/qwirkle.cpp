
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

    if (option == 1) {
      newGame();
      std::cout << std::endl;
      option = 4;
    }
    if (option == 2) {
      loadGame();
      std::cout << std::endl;
      option = 4;
    }
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
  bool endGame = false;

  //takes input of how many players and loops until valid or ^D
  while (validate == false){
    std::cout << std::endl
    << "Enter amount of players:" << std::endl
    << "> ";
    std::string input = "";
    std::cin >> input;
    //if input is eof then it exits
    if (std::cin.eof()){
      endGame = true;
      validate = true;
    }
    else{
      //checks that the input is between 2 and 4
      if (checkStringCharBetween(input, '2', '4') == true
          && input.length() == 1) {
            validate = true;
            amountOfPlayers = input.at(0) - '0';
      }
      else std::cout << "Error - Amount must be between 1 and 5" << std::endl;
    }
  }

  //array for all player names
  std::string playerList[NUMBER_OF_PLAYERS];

  //loop to prompt for players to however many players are playing
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++){
    playerList[i] = "";
  }

  //for each numper of players it prompts the user for a player name
  for (int i = 0; i < amountOfPlayers && endGame == false; i++){
    std::string player = promptForPlayer(i+1);
    if (std::cin.eof()) endGame = true;
    else playerList[i] = player;
  }

  //TODO implement the creation of the game using the array of players
  if (endGame == false){
    std::cout << std::endl;
    GameEngine(playerList, amountOfPlayers);

  }
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
  std::ifstream inFile("../src/"+input);

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
          currentLine++;
          tempHand = lines[currentLine];

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
      }
      currentLine++;
      //check bag
      String bag= lines[currentLine];
      currentLine++;
      String turnString = lines[currentLine];
      int turn= std::stoi(turnString);
      new GameEngine(playerNum, initRowLength, initColLength, playerNames,
                         playerScores, playerHands, board, bag, turn);
      }
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
  //loop until the input is correct
  while (validated == false){
    std::string input = "";
    std::cin >> input;
    //if input is ^D then it exits else is becomes an int
    if (std::cin.eof()) option = 4;
    else option = input.at(0) - '0';
    //if it is one of the options then it is valid
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

    if (!std::cin.eof()){
      //check input is all upper case letters
      validate = checkStringCharBetween(player, 'A', 'Z');

      //prints error message if incorrect
      if (validate == false)
        std::cout << "Error - Must be uppercase characters" << std::endl << "> ";
    }
    else{
      validate = true;
    }
  }

  return player;
}

//checks a given string that each character is between a min and max chars
bool checkStringCharBetween(std::string str, char min, char max){
  bool validate = true;
  //for loop to iterate through each character in the string
  for (int i = 0; str[i] != '\0'; i++){
    //if the character is not within the range it becomes invalid
    if (str.at(i) < min || str.at(i) > max) validate = false;
  }
  return validate;
}
