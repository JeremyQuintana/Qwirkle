#include "Player.h"

Player::Player(std::string name, LinkedList* hand){
  this->name = name;
  this->hand = hand;
}

String Player::handToString(){
  return hand->listToString();
}

Tile* Player::getTilePtr(Tile tileToUse){
  Tile* tile = nullptr;
  bool found = false;
  for (int i = 0; found == false && i < hand->size(); i++){
    Tile* tempTile = hand->get(i);
    if (tempTile->getValue() == tileToUse.getValue()){
      tile = tempTile;
      found = true;
    }
  }
  return tile;
}

void Player::addTile(Tile* tileToAdd){
  hand->addBack(tileToAdd);
}
void Player::removeTile(Tile tileToRemove){
  hand->deleteTile(tileToRemove);
}

void Player::addScore(int award){
  score += award;
}

int Player::getScore(){
  return score;
}

std::string Player::getName(){
  return name;
}
