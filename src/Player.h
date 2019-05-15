#ifndef SRC_PLAYER_H
#define SRC_PLAYER_H

#include "LinkedList.h"

class Player {
public:
  Player(std::string name, LinkedList* hand);
  ~Player();
  int getScore();
  String handTostring();
  Tile getTile(Tile tileToUse);
  void addTile(Tile tileToAdd);
  void removeTile(Tile tileToRemove);
  void addScore(int score);

private:
  std::string name;
  int score = 0;
  LinkedList* hand;
};

#endif
