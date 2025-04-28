#ifndef MAN_H
#define MAN_H

#include "Player.h"

class Man : public Player {
public:
    Man(Mathable* game);
    void makeMove() override;
    ~Man() override;
};

// A helper function prototype
void handleInvalidInput();

#endif // MAN_H