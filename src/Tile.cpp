
#include "Tile.h"

Tile::Tile(){
}

Tile::Tile(Colour colour, Shape shape){
    this->colour= colour;
    this->shape= shape;
}

Tile::Tile(std::string attribute){
    std::string colour= attribute.substr(0,1);
    std::string shape= attribute.substr(1,1);
    this->colour= colour[0];
    this->shape= std::stoi(shape);
}

String Tile::getValue() {
    return colour + std::to_string(shape);
}

Tile::~Tile(){
  
}
//gets the value of tile tile which includes the colour and the shape not separated by comma or space in string
