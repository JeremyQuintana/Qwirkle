
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <random>

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int size();
   void clear();
<<<<<<< HEAD
   Tile get(int i); //Find and return tile at index
=======
   Tile* get(int i); //Find
>>>>>>> e4dfb62e853f547b77d7a07bcea5d90260d05c06

   void addFront(Tile* data);
   void addBack(Tile* data);

   void deleteFront();
   void deleteBack();
   void deleteTile(Tile data); //Delete a specific tile

   bool inList(Tile data); //Check if tile is in list
   std::string listToString();

   void shuffle(); // Shuffles list

private:
 
   Node* head;
   Node* tail;
   int count;

};

#endif // ASSIGN2_LINKEDLIST_H

