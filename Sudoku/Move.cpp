/* 
 * File:   Move.cpp
 * Author: HenryDaniels-Koch
 * 
 * Created on April 11, 2015, 12:57 PM
 */


#include "Move.h"


Move::Move(int r, int c, int value) {
    row = r;
    col = c;
    this->value=value;
}

int Move::getRow() {
    return row;
}

int Move::getCol() {
    return col;
}

int Move::getValue() {
    return value;
}
