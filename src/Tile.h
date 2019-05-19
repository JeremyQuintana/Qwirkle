
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
   // Public. Can point to
   Colour colour;
   Shape  shape;

   Tile();
   Tile(Colour, Shape);
   String getValue();
   ~Tile();

   String getValue();
};

#endif // ASSIGN2_TILE_H
