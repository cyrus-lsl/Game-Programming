// Name: Lee Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#include <iostream>
#include <iomanip>
#include <cassert>
#include "Mathable.h"
#include "BonusSquare.h"
#include "RestrictionSquare.h"


using namespace std;

Mathable::Mathable(int seed) {
    rng = new RandomNumberGenerator(seed);
    setUpBag();
    setUpBoard();
}

// Return the number of tokens in the bag
int Mathable::bagSize() const {
    return int(bag.size());
}

// Fill up the bag with shuffled tokens based on official game's token listing
void Mathable::setUpBag() {
    assert(T == 60 && "Token count differs from official one!");
    for (int i = 1; i <= 20; i++) {
        for (int k = 0; k < (i > 10 ? 1 : 5); k++) {
            bag.push_back(Token(i));
        }
    }
    rng->shuffle(bag);
}

// Draw tokens from the bag to fill up the specified rack as far as possible
// (up to max. size R), and return the count of tokens drawn
int Mathable::drawTokens(vector<Token> &rack) {
    int drawn = 0, rackSize = rack.size();
    for (int i = 0; i < R - rackSize; i++) {
        if (!bag.empty()) {
            rack.push_back(bag.back());
            bag.pop_back();
            drawn++;
        }                
    }
    return drawn;
}

// Print the tokens contained the bag (for debugging purpose)
void Mathable::printBag() const {
    const int LINE_WIDTH = 20;
    for (unsigned i = 1; i <= bag.size(); i++) {
        cout << setw(2) << bag.at(i - 1) << " ";
        if (i % LINE_WIDTH == 0 || i == bag.size())
            cout << endl;
    }  
}

// Set up the game board with central tokens and special squares
void Mathable::setUpBoard() {
    assert(N % 2 == 0 && "Board size must be even!");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = new Square;
        }
    }
    // Place central tokens
    int a = N/2, b = N/2 - 1; 
    board[b][b]->fill(Token(1));
    board[b][a]->fill(Token(2));
    board[a][b]->fill(Token(3));
    board[a][a]->fill(Token(4));

    // Restriction squares
    board[4][2] = new RestrictionSquare('x'); 
    board[5][2] = new RestrictionSquare('/');
    board[4][7] = new RestrictionSquare('x'); 
    board[5][7] = new RestrictionSquare('/');
    board[2][4] = new RestrictionSquare('+'); 
    board[2][5] = new RestrictionSquare('-');
    board[7][4] = new RestrictionSquare('+'); 
    board[7][5] = new RestrictionSquare('-');

    // Bonus squares
    int bs[20][3] = {
        {0, 0, 3}, {1, 1, 2}, {2, 2, 2}, {7, 7, 2}, {8, 8, 2}, 
        {9, 9, 3}, {0, 4, 2}, {0, 5, 2}, {9, 4, 2}, {9, 5, 2},
        {4, 0, 3}, {5, 0, 3}, {4, 9, 3}, {5, 9, 3}, {9, 0, 3}, 
        {8, 1, 2}, {7, 2, 2}, {0, 9, 3}, {1, 8, 2}, {2, 7, 2}
    };
    for (int i = 0; i < 20; i++) {
        int y = bs[i][0], x = bs[i][1], m = bs[i][2];
        board[y][x] = new BonusSquare(m);
    }
}

// Print the game board
void Mathable::printBoard() const {
    // Print column headers
    cout << "   ";
    for (int i = 0; i < N; i++)
        cout << setw(3) << char('A' + i);
    cout << endl;
    
    // Print row headings and cells
    for (int i = 0; i < N; i++) {
        cout << setw(2) << i + 1 << " |";
        for (int j = 0; j < N; j++) {
            cout << setw(2) << *board[i][j] << '|';
        }
        cout << endl;
    }
}

// Return true if the cell at row y and column x is within the board dimensions,
// and false otherwise (i.e., outside the board)
bool Mathable::isValidCell(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

// Return the points gained by the move of placing token at board[y][x].
// The move is invalid if the return value is 0. 
int Mathable::evalMove(Token token, int y, int x) const {
    // TODO: ...
    int point = 0;
    if (!isValidCell(y, x)) return 0;
    else if (!(board[y][x]->empty())) return 0;
    else if (RestrictionSquare* rs = dynamic_cast<RestrictionSquare*>(board[y][x])) {
        Token t1, t2;
        char mo = rs->getMathOperator();
        if (y > 1 && (board[y-1][x]->getToken() != 0 && board[y-2][x]->getToken() != 0)) {
            t1 = board[y-1][x]->getToken();
            t2 = board[y-2][x]->getToken();
            if (mo == '+' && t1 + t2 == token) point += token;
            else if (mo == '-' && abs(t1 - t2) == token) point += token;
            else if (mo == 'x' && t1 * t2 == token) point += token;
            else if ((mo == '/' && t1 / t2 == token && t1 % t2 == 0) || (t2 / t1 == token && t2 % t1 == 0)) point += token;
        }
        if (y < N-3 && (board[y+1][x]->getToken() != 0 && board[y+2][x]->getToken() != 0)) {
            t1 = board[y+1][x]->getToken();
            t2 = board[y+2][x]->getToken();
            if (mo == '+' && t1 + t2 == token) point += token;
            else if (mo == '-' && abs(t1 - t2) == token) point += token;
            else if (mo == 'x' && t1 * t2 == token) point += token;
            else if ((mo == '/' && t1 / t2 == token && t1 % t2 == 0) || (t2 / t1 == token && t2 % t1 == 0)) point += token;
        }
        if (x > 1 && (board[y][x-1]->getToken() != 0 && board[y][x-2]->getToken() != 0)) {
            t1 = board[y][x-1]->getToken();
            t2 = board[y][x-2]->getToken();
            if (mo == '+' && t1 + t2 == token) point += token;
            else if (mo == '-' && abs(t1 - t2) == token) point += token;
            else if (mo == 'x' && t1 * t2 == token) point += token;
            else if ((mo == '/' && t1 / t2 == token && t1 % t2 == 0) || (t2 / t1 == token && t2 % t1 == 0)) point += token;
        }
        if (x < N-3 && (board[y][x+1]->getToken() != 0 && board[y][x+2]->getToken() != 0)) {
            t1 = board[y][x+1]->getToken();
            t2 = board[y][x+2]->getToken();
            if (mo == '+' && t1 + t2 == token) point += token;
            else if (mo == '-' && abs(t1 - t2) == token) point += token;
            else if (mo == 'x' && t1 * t2 == token) point += token;
            else if ((mo == '/' && t1 / t2 == token && t1 % t2 == 0) || (t2 / t1 == token && t2 % t1 == 0)) point += token;
        }
    }
    else {
        Token t1, t2;
        if (y > 1 && (board[y-1][x]->getToken() != 0 && board[y-2][x]->getToken() != 0)) {
            t1 = board[y-1][x]->getToken();
            t2 = board[y-2][x]->getToken();
            if (t1 + t2 == token) point += token;
            else if (abs(t1 - t2) == token) point += token;
            else if (t1 * t2 == token) point += token;
            else if ((t1 / t2 == token && t1 % t2 == 0) || (t2 / t1 == token && t2 % t1 == 0)) point += token;
        }
        if (y < N-3 && (board[y+1][x]->getToken() != 0 && board[y+2][x]->getToken() != 0)) {
            t1 = board[y+1][x]->getToken();
            t2 = board[y+2][x]->getToken();
            if (t1 + t2 == token) point += token;
            else if (abs(t1 - t2) == token) point += token;
            else if (t1 * t2 == token) point += token;
            else if ((t1 / t2 == token && t1 % t2 == 0) || (t2 / t1 == token && t2 % t1 == 0)) point += token;
        }
        if (x > 1 && (board[y][x-1]->getToken() != 0 && board[y][x-2]->getToken() != 0)) {
            t1 = board[y][x-1]->getToken();
            t2 = board[y][x-2]->getToken();
            if (t1 + t2 == token) point += token;
            else if (abs(t1 - t2) == token) point += token;
            else if (t1 * t2 == token) point += token;
            else if ((t1 / t2 == token && t1 % t2 == 0) || (t2 / t1 == token && t2 % t1 == 0)) point += token;
        }
        if (x < N-3 && (board[y][x+1]->getToken() != 0 && board[y][x+2]->getToken() != 0)) {
            t1 = board[y][x+1]->getToken();
            t2 = board[y][x+2]->getToken();
            if (t1 + t2 == token) point += token;
            else if (abs(t1 - t2) == token) point += token;
            else if (t1 * t2 == token) point += token;
            else if ((t1 / t2 == token && t1 % t2 == 0) || (t2 / t1 == token && t2 % t1 == 0)) point += token;
        }
        if (BonusSquare* bs = dynamic_cast<BonusSquare*>(board[y][x])) {
            point *= bs->getMultiplier();
        }
    }
    return point;
};

// Place token at the square at position (y, x).
void Mathable::place(Token token, int y, int x) {
    // TODO: ...
    board[y][x]->fill(token);
}

// Return a vector of possible moves found on the game board using the tokens
// in the specified vector representing a player's rack.
vector<Move> Mathable::possibleMoves(const vector<Token> &rack) const {
    vector<Move> Move;
    for (int j = 0 ; j < N ; j++) {
        for (int i = 0 ; i < N ; i++) {
            if (!(board[j][i]->empty())) continue;
            for (int k = 0 ; k < rack.size() ; k++) {
                int tmp = evalMove(rack[k], j, i);
                if (tmp != 0) {
                    struct Move move;
                    move.y = j;
                    move.x = i;
                    move.token = rack[k];
                    move.rackPos = k;
                    move.points = tmp;
                    
                    Move.push_back(move);
                }
            }
        }
    }
    return Move;
}


// Destructor
Mathable::~Mathable() { 
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            delete board[i][j];
        }
    }
}
