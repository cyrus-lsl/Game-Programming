#ifndef RESTRICTION_SQUARE_H
#define RESTRICTION_SQUARE_H

#include "Square.h"

class RestrictionSquare : public Square {
public:
    RestrictionSquare(char op);
    char getMathOperator() const;
    std::string toString() const override;
private:
    char mathOperator;
};

#endif  // RESTRICTION_SQUARE_H
