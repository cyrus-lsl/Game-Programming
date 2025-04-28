// Name: Lee Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#include <iostream>
#include <cctype>     // for toupper()
#include <limits>     // for numeric_limits
#include "Man.h"

using namespace std;

// A helper function for handling invalid input by printing the error 
// message, resetting the state of the input stream cin, and clearing the 
// input buffer for any leftover characters that may remain in the input 
// stream after a previous failed input operation.
void handleInvalidInput() {
    cout << "Invalid input!" << endl;
    cin.clear();  // clear the error state
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

Man::Man(Mathable* game) : Player(game) {
}

// This function overrides the pure virtual function in the superclass
// to prompt the user for a valid move using a token in this player's rack
// and carry it out on the game board.
void Man::makeMove() {
    char char_x;
    int x, y;
    int token;
    int rackPos = 0;
    int tmp = 0;
    int points = 0;
    while(1) {
        cout << "Enter move: ";
        cin >> char_x >> y >> token;
        x = toupper(char_x) - 'A';
        y -= 1;
        for (int i = 0 ; i < R ; i++) {
            if (token == rack[i]) {
                tmp++;
                rackPos = i;
                break;
            }
        }
        points = mGame->evalMove(token, y, x);
        if (tmp == 0 || points == 0) {
                cout << "Invalid input!" << endl;
        }
        else break;
    }
    mGame->place(token, y, x);
    rack.erase(rack.begin() + rackPos);
    score += points;
}

// Destructor
Man::~Man() {
}
