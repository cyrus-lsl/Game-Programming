// Name: Lee Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#ifndef BONUS_SQUARE_H
#define BONUS_SQUARE_H

// TODO: 
// Define the BonusSquare class which inherits from the Square class.
// Refer to our specification to know what data members and member 
// functions this class should have.
#include "Square.h"

class BonusSquare : public Square {
public:
    BonusSquare(int times);
    int getMultiplier() const;
    std::string toString() const override;
private:
    int multiplier;
};

#endif  // BONUS_SQUARE_H
