// Name: Lee Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#include "RestrictionSquare.h"

RestrictionSquare::RestrictionSquare(char op)
	: mathOperator(op) {
}

char RestrictionSquare::getMathOperator() const {
    return mathOperator;
}

std::string RestrictionSquare::toString() const {
    if (empty()) {
        return std::string(1, mathOperator);
    }
    else {
        return std::string(1, getToken());
    }
}
