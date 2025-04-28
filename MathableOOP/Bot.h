#ifndef BOT_H
#define BOT_H

#include "Player.h"

class Bot : public Player {
public:
    Bot(Mathable* game);
    void makeMove() override;
    ~Bot() override;
};

#endif // BOT_H