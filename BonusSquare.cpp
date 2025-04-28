// Name: Lee Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

// TODO: 
// Add code to implement the member functions of the BonusSquare class.
#include "BonusSquare.h"

BonusSquare::BonusSquare(int times)
: multiplier(times) {
}

int BonusSquare::getMultiplier() const {
    return multiplier;
}

std::string BonusSquare::toString() const {
    if (empty()) {
        return std::to_string(multiplier) + "x";
    }
    else {
        return std::to_string(getToken());
    }
}
