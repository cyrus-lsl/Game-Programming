// Name: Lee Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#include <iostream>
#include "Bot.h"

using namespace std;

Bot::Bot(Mathable* game) : Player(game) {
}

// This function overrides the pure virtual function in the superclass
// to pick and carry out the best possible move (greedy solution: the 
// one with the highest points) using this player's rack.
void Bot::makeMove() {
   vector <Move> move = mGame->possibleMoves(rack);
    Move bestMove = move[0];
    for (int i = 0 ; i < move.size() ; i++) {
        if (move[i].points > bestMove.points) {
            bestMove = move[i]; 
        }
    }
    mGame->place(bestMove.token, bestMove.y, bestMove.x);
    rack.erase(rack.begin() + bestMove.rackPos);
    score += bestMove.points;
    cout << "Played move: " << char('A' + bestMove.x) << bestMove.y + 1 << " " << bestMove.token << "\n";
}

// Destructor
Bot::~Bot() {
}
