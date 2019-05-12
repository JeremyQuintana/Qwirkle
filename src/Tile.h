
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H
#include <iostream>
#include <string>

typedef std::string String;

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;

   char getColour();
   int getShape();
   String getValue();
   void setShape(int);
   void setColour(char);
   bool isPlacementValid();

   Tile();
   Tile(char, int);
   ~Tile();

};

#endif // ASSIGN2_TILE_H
