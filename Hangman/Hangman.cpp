#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Hangman.h"
using namespace std;


Hangman::Hangman(string fname, unsigned s){
    importDictionary(fname);
    won = 0;
    lost = 0;
    srand(s);
    restart();
}

int Hangman::getWon() const {
    return won;
}

int Hangman::getLost() const {
    return lost;
}

string Hangman::getSecretWord() const {
    if (wordToGuess == secretWord || chances == 0)
        return secretWord;
    else
        return "";
}

void Hangman::printGame() const {
    cout << "+--+-" << endl;
    
    cout << "| ";
    if (chances < 4)
        cout << "\\";
    else
        cout << " ";
    if (chances == 6)
        cout << " ";
    else
        cout << "O";
    if (chances < 3)
        cout << "/";
    else
        cout << " ";
    cout << endl;
    
    cout << "|  ";
    if (chances < 5)
        cout << "|";
    else
        cout << " ";
    cout << " " << endl;
    
    cout << "| ";
    
    if (chances <= 1)
        cout << "/ ";
    else
        cout << "  ";
    
    if (chances != 0)
        cout << " " << endl;
    else
        cout << "\\" << endl;
    
    cout << "|" << endl;
    
    cout << "Word to guess: " << wordToGuess << endl;
    cout << "Failed letters:";
    for (int i = 0 ; i < guessedLetters.size() ; i++) {
        if (secretWord.find(guessedLetters[i]) == -1) {
            cout << " " << guessedLetters[i];
        }
    }
    cout << endl;
    cout << "Chances left: " << chances << endl;
}

int Hangman::guessOneLetter(char ch){
    int tmp = 0, r;
    for (int i = 0 ; i < guessedLetters.size() ; i++){
        if (guessedLetters[i] == ch)
            tmp++;
    }
    if (tmp != 0) {
        r = 2;
        return 2;
    }
    
    
    guessedLetters.push_back(ch);
    if (secretWord.find(ch) == -1){
        chances--;
    }
    if (chances == 0) {
        lost++;
        r = 0;
        return r;
    }
    
    if (secretWord.find(ch) != -1) {
        for (int i = 0 ; i < secretWord.size() ; i++) {
            if (ch == secretWord[i])
                wordToGuess[i] = ch;
        }
    }
    if (wordToGuess == secretWord) {
        won++;
        r = 1;
        return r;
    }
    
    return 3;
}

void Hangman::restart() {
    size_t n = dictionary.size();
    int k = rand() % n;
    
    wordToGuess.resize(0);
    
    secretWord = dictionary.at(k);
    for (int i = 1 ; i <= secretWord.size() ; i++){
        wordToGuess = wordToGuess + "_";
    }
    
    guessedLetters.resize(0);
    
    chances = 6;
}

void Hangman::importDictionary(string fname) {
    int i, n;
    string s;
    ifstream fin(fname.c_str());

    if (fin.fail()) {
        cout << "File not found: " << fname << endl;
        exit(1);
    }

    fin >> n;
    for (i = 0; i < n; i++) {
        fin >> s;
        dictionary.push_back(s);
    }
    fin.close();
}

