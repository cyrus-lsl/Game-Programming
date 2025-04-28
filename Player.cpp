// Name: Lee Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#include <iostream>
#include "Player.h"

using namespace std;

Player::Player(Mathable* game) : mGame(game), score(0) {
    mGame->drawTokens(rack);
}

// Print the rack of this player 
void Player::printRack() const {
    cout << "[ ";
    for (const Token tok : rack)
        cout << tok << ' ';
    cout << ']' << endl;
}

// Return the number of tokens in the rack of the player
int Player::rackSize() const {
    // TODO: ...
    return rack.size();
}

// Refill the rack and return the number of new tokens drawn from the bag
int Player::refillRack() {
    // TODO: ...
    return mGame->drawTokens(rack);
}

// Return true if there exist at least one move for this player 
// and false otherwise
bool Player::anyMove() const {
    // TODO: ...
    std::vector<Move> moves = mGame->possibleMoves(rack);
    return !moves.empty();
}

// Return the score obtained by the player so far
int Player::getScore() const {
    // TODO: ...
    return score;
}

// Destructor
Player::~Player() {
}
