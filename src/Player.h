#ifndef SRC_PLAYER_H
#define SRC_PLAYER_H

#include "LinkedList.h"

using std::cin;

class Player {
public:
  Player(std::string name, LinkedList* hand);
  ~Player();
  int getScore();
  String handToString();
  Tile* getTilePtr(Tile tileToUse);
  void addTile(Tile* tileToAdd);
  void removeTile(Tile tileToRemove);
  void addScore(int award);

private:
  std::string name;
  int score = 0;
  LinkedList* hand;
};

#endif
