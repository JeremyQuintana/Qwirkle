
#include "Tile.h"

Tile::Tile(){
    shape = 0;
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