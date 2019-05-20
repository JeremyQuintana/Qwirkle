
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int size();
   void clear();
   Tile* get(int i); //Find

   void addFront(Tile* data);
   void addBack(Tile* data);

   void deleteFront();
   void deleteBack();
   void deleteTile(Tile data); //Delete a specific tile

   bool inList(Tile data); //Check if tile is in list
   std::string listToString();

private:
   Node* head;
   Node* tail;
   int count;

};

#endif // ASSIGN2_LINKEDLIST_H
