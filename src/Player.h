#ifndef SRC_PLAYER_H
#define SRC_PLAYER_H

#include "LinkedList.h"

class Player {
public:
  Player(std::string name, LinkedList* hand);
  ~Player();
  int getScore();
  LinkedList* getHand();
  bool useTile(Tile tileToUse);
  bool replaceTile(Tile bagTile, Tile toReplace);

private:
  std::string name;
  int score = 0;
  LinkedList* hand;
};

#endif
