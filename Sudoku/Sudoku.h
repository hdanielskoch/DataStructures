/* 
 * File:   Sudoku.h
 * Author: HenryDaniels-Koch
 *
 * Created on April 11, 2015, 12:56 PM
 */

#ifndef SUDOKU_H
#define	SUDOKU_H


#include "Board.h"
#include "Move.h"
#include <stack>

using namespace std;

class Sudoku {
    
public:
    
    void Sudoku();
    void Solve();
private:
    Board theBoard;
    stack <move> moves;
};

#endif	/* SUDOKU_H */


