/* 
 * File:   Move.h
 * Author: HenryDaniels-Koch
 *
 * Created on April 11, 2015, 12:57 PM
 */

#ifndef MOVE_H
#define	MOVE_H


class Move {
public:
    Move(int r,int c, int value);
    int getRow();
    int getCol();
    int getValue();
private:
    int row;
    int col;
    int value;
};

#endif	/* MOVE_H */
