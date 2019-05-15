
#include "Tile.h"

Tile::Tile(){
}

Tile::Tile(Colour colour, Shape shape){
    this->colour= colour;
    this->shape= shape;
}

String Tile::getValue() {
    return String(colour, 1) + std::to_string(shape);
}
//gets the value of tile tile which includes the colour and the shape not separated by comma or space in string