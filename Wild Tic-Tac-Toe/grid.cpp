// Name: LEE Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#include "grid.h"
#include <iostream>
using namespace std;

/* Prints grid to the screen. */
void printGrid(int grid) {
   char p1, p2, p3, p4, p5, p6, p7, p8, p9;   // Positions 1-9
   int d;
    
   d = grid / 100000000;
   p1 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));
   d = grid / 10000000 % 10;
   p2 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));
   d = grid / 1000000 % 10;
   p3 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));
   d = grid / 100000 % 10;
   p4 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));
   d = grid / 10000 % 10;
   p5 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));
   d = grid / 1000 % 10;
   p6 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));
   d = grid / 100 % 10;
   p7 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));
   d = grid / 10 % 10;
   p8 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));
   d = grid % 10;
   p9 = (d == 1 ? 'X' : (d == 2 ? 'O' : ' '));

   cout << " " << p1 << " | " << p2 << " | " << p3 << endl;
   cout << "---+---+---" << endl;
   cout << " " << p4 << " | " << p5 << " | " << p6 << endl;
   cout << "---+---+---" << endl;
   cout << " " << p7 << " | " << p8 << " | " << p9 << endl;
}

/* Returns whether position pos of grid is already filled with a mark */
bool isFilled(int grid, int pos) {
    // TODO; add a return statement in order to compile
    int temp = 1;
    for (int n = 1 ; n < 10-pos ; n++){
        temp *= 10;
    }
    temp = grid / temp;
    return temp % 10 != 0;
}

/* Models the game move from a player putting a mark in position pos of grid.
   Returns true if a horizontal/vertical/diagonal line of three same marks is
   formed. */
bool updateGrid(int &grid, int pos, char mark) {
    // TODO; add a return statement in order to compile
    int temp = 1;
    if (mark == 'X'){
        mark = 1;
    }
    else mark = 2;
    for (int n = 1 ; n < 10-pos ; n++){
        temp *= 10;
    }
    grid += mark * temp;
    
    int a0 = grid / 100000000 % 10;
    int a1 = grid / 10000000 % 10;
    int a2 = grid / 1000000 % 10;
    int a3 = grid / 100000 % 10;
    int a4 = grid / 10000 % 10;
    int a5 = grid / 1000 % 10;
    int a6 = grid / 100 % 10;
    int a7 = grid / 10 % 10;
    int a8 = grid % 10;

    if ((a0 == a1 && a1 == a2 && a0 != 0) ||
        (a3 == a4 && a4 == a5 && a3 != 0) ||
        (a6 == a7 && a7 == a8 && a6 != 0)) {
        return true;
    }

    if ((a0 == a3 && a3 == a6 && a0 != 0) ||
        (a1 == a4 && a4 == a7 && a1 != 0) ||
        (a2 == a5 && a5 == a8 && a2 != 0)) {
        return true;
    }

    if ((a0 == a4 && a4 == a8 && a0 != 0) ||
        (a2 == a4 && a4 == a6 && a2 != 0)) {
        return true;
    }

    return false;
}
