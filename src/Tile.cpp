
#include "Tile.h"

Tile::Tile(){
}

Tile::Tile(Colour colour, Shape shape){
    this->colour= colour;
    this->shape= shape;
}

String Tile::getValue() {
    return colour + std::to_string(shape);
}

Tile::~Tile(){
  
}
//gets the value of tile tile which includes the colour and the shape not separated by comma or space in string
