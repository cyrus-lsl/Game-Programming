#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator(unsigned seed) 
    : current(seed) {
}

// Generate the next random number
unsigned RandomNumberGenerator::next() {
    current = (a * current + c) % m;
    return current;
}

// Shuffle elements of a vector using the Fisher-Yates algorithm
void RandomNumberGenerator::shuffle(std::vector<int>& vec) { 
    for (unsigned i = vec.size() - 1; i > 0; i--) {
        unsigned j = next() % (i + 1); // random index from 0 to i
        std::swap(vec[i], vec[j]);
    }
}
