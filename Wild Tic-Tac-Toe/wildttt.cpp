// Name: LEE Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#include "grid.h"
#include <iostream>
using namespace std;

/* game flow */
int main() {
    int grid = 0, pos;
    char mark;

    
    while(1){
        for (int i = 1 ; i <= 2 ; i++){
            printGrid(grid);
            
            while(1){
                cout << "Player " << i <<"'s move: ";
                cin >> mark >> pos;
                if ((mark != 'X' && mark != 'O') || pos < 1 || pos > 9 || isFilled(grid, pos)){
                    cout << "Invalid! Try again." << endl;
                }
                else break;
            }
            
            if(updateGrid(grid, pos, mark)){
                printGrid(grid);
                cout << "Player " << i << " wins!" << endl;
                return 0;
            }
            
            if (grid / 100000000 % 10 != 0 && grid / 10000000 % 10 != 0 && grid / 1000000 % 10 != 0 && grid / 100000 % 10 != 0 && grid / 10000 % 10 != 0 && grid / 1000 % 10 != 0 && grid / 100 % 10 != 0 && grid / 10 % 10 != 0 && grid % 10 != 0){
                printGrid(grid);
                cout << "Draw game!" << endl;
                return 0;
            }
        }
    }
}
