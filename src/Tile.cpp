
#include "Tile.h"

Tile::Tile(){
}

Tile::Tile(char colour, int shape){
    this->colour= colour;
    this->shape= shape;
}

String Tile::getValue() {
    return String(colour, 1) + std::to_string(shape);
}

char Tile::getColour() {
    return colour;
}

int Tile::getShape() {
    return getShape();
}

void Tile::setColour(char colour) {
    this->colour= colour;
}

void Tile::setShape(int shape) {
    this->shape= shape;
}