#include <iostream>
#include "Square.h"

using namespace std;

Square::Square() : filled(false), token(0) {
}

// Return true if this square is not filled with a token and false otherwise.
bool Square::empty() const {
    return !filled;
}

// Getter method for the token field.
Token Square::getToken() const {
    return token;
}

// Setter method for writing token to tok and filled to true
void Square::fill(Token tok) {
    if (filled) {
        cout << "This square has been filled already!" << endl;
        return;
    }
    token = tok;
    filled = true;
}

// Return a string representation of the square
std::string Square::toString() const {
    if (filled)
        return std::to_string(token);
    return "__";   // represents an empty square
}

// Overload the << operator for printing a Square object to standard output
ostream &operator<<(ostream &os, Square &sq) {
    return os << sq.toString();
}
