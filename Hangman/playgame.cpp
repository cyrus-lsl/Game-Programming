#include <iostream>
#include "Hangman.h"

using namespace std;

int main() {
    string fname;
    int s;
    char ch, tmp;
    cout << "Dictionary file name? ";
    cin >> fname;
    cout << "Seed? ";
    while (1) {
        cin >> s;Hangman Hangman(fname, s);
        while (1) {
            Hangman.printGame();
            while (1) {
                while (1) {
                    cout << "Guess a letter? ";
                    cin >> ch;
                    ch = tolower(ch);
                    if (!(ch - 'a' >= 0 && ch - 'z' <= 0)) {
                        cout << "Must be a letter. Enter again!" << endl;
                    }
                    else
                        break;
                }
                int control = Hangman.guessOneLetter(ch);
                if (control == 0) {
                    Hangman.printGame();
                    cout << "Oh no!";
                }
                if (control == 1) {
                    Hangman.printGame();
                    cout << "Bingo!";
                }
                if (control == 0 || control == 1) {
                    cout << " Secret word is: " << Hangman.getSecretWord() << endl;
                    cout << "Type Y or y to play another game? ";
                    cin >> tmp;
                    if (tmp == 'Y' || tmp == 'y') {
                        Hangman.restart();
                        break;
                    }
                    else {
                        cout << Hangman.getWon() + Hangman.getLost() << " game(s) played." << endl;
                        cout << Hangman.getWon() << " game(s) won." << endl;
                        cout << Hangman.getLost() << " game(s) lost." << endl;
                        return 0;
                    }
                }
                if (control == 2) {
                    cout << "Letter " << ch << " already tried. Enter again! " << endl;
                    Hangman.printGame();
                }
                    
                if (control == 3)
                    break;
            }
        }
    }
}
