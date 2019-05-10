#include "Player.h"

Player::Player(std::string name, LinkedList* hand){
  this->name = name;
  this->hand = hand;
}

bool Player::useTile(Tile tileToUse){
  bool validTile = false;
  if (hand->inList(tileToUse) == true){
    hand->deleteTile(tileToUse);
    validTile = true;
  }

  return validTile;
}

bool Player::replaceTile(Tile bagTile, Tile toReplace){
  bool validReplace = false;
  if (hand->inList(toReplace) == true){
    hand->deleteTile(toReplace);
    hand->addFront(bagTile);
    validReplace = true;
  }

  return validReplace;
}

LinkedList* Player::getHand(){
  return hand;
}

int Player::getScore(){
  return score;
}
