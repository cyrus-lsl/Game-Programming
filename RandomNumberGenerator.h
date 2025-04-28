#ifndef RNG_H
#define RNG_H

#include <vector>

class RandomNumberGenerator {
public:
    RandomNumberGenerator(unsigned seed);
    unsigned next();
    void shuffle(std::vector<int>& vec);
private:
    unsigned current;                      // Current state
    static const unsigned a = 1103515245;  // Multiplier
    static const unsigned c = 12345;       // Increment
    static const unsigned m = 2147483648;  // 2^31
};

#endif  // RNG_H
