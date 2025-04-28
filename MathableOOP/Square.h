#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <string>

using Token = int;     // Alias of int type

class Square {
    friend std::ostream &operator<<(std::ostream &os, Square &sq);
public:
    Square();
    bool empty() const;
    Token getToken() const;
    void fill(Token tok);
    virtual std::string toString() const;
private:
    bool filled;
    Token token;
};

#endif  // SQUARE_H
