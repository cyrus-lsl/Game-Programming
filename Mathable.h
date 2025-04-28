#ifndef MATHABLE_H
#define MATHABLE_H

#include <vector>
#include "Square.h"
#include "RandomNumberGenerator.h"

// Global constants
const int P = 4;       // Maximum # players
const int N = 10;      // Board size
const int R = 5;       // Rack size
const int T = 60;      // Bag size (total # tokens)

struct Move {
    int y;        // row id of the move's target square
    int x;        // column id of the move's target square
    int token;    // token to be placed at (y, x) on the board
    int rackPos;  // the index of token in the player's rack
    int points;   // number of points gained by the move
};

class Mathable {
public:
    Mathable(int seed);
    int bagSize() const;
    int drawTokens(std::vector<Token> &rack);
    void printBag() const;
    void printBoard() const;
    int evalMove(Token token, int y, int x) const;
    void place(Token token, int y, int x);
    std::vector<Move> possibleMoves(const std::vector<Token> &rack) const;
    static bool isValidCell(int y, int x);
    ~Mathable();  // Destructor
private:
    void setUpBag();
    void setUpBoard();
    Square* board[N][N];         // Game board
    std::vector<Token> bag;      // Bag of tokens
    RandomNumberGenerator* rng;  // Random number generator
};

#endif // MATHABLE_H
