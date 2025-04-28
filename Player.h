#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Mathable.h"

class Player {
public:
    Player(Mathable* game);
    void printRack() const;
    int refillRack();
    int rackSize() const;
    int getScore() const;
    bool anyMove() const;
    virtual void makeMove() = 0;
    virtual ~Player();
protected:
    Mathable* mGame;
    std::vector<Token> rack;
    int score;
};

#endif  // PLAYER_H
