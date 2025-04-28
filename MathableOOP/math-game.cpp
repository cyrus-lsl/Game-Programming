// Name: Lee Shun Long
// Student ID: 1155211573
// Email: 1155211573@link.cuhk.edu.hk

#include <iostream>
#include "Bot.h"
#include "Man.h"
#include "Mathable.h"

using namespace std;

int main() {
    int seed;
    cout << "Enter seed: ";
    cin >> seed;

    int h, m;
    cout << "Enter # human and machine players: ";
    cin >> h >> m;
    if (h < 0 || m < 0 || h + m < 2 || h + m > P) {
        cout << "Invalid number of players!" << endl;
        exit(1);
    }

    Mathable* game = new Mathable(seed);  // Access board and bag via game
    vector<Player*> players(h + m);       // List of players
    for (int i = 0; i < h + m; i++) {
        if (i < h)
            players.at(i) = new Man(game);
        else
            players.at(i) = new Bot(game);
    }

    // main loop
    int round = 0;
    while (true) {
        for (int i = 0; i < players.size(); i++) {
            round++;
            cout << "Round " << round << endl;
            Player* currentPlayer = players[i];
            cout << "Player " << (i + 1) << " (";
            if (dynamic_cast<Man*>(currentPlayer))
                cout << "Man)" << endl;
            else
                cout << "Bot)" << endl;
            
            cout << "--------------" << endl;
            
            while(true) {
                cout << "Bag (" << game->bagSize() << " tokens)" << endl;
                game->printBoard();
                cout << "Score: " << currentPlayer->getScore() << endl;
                cout << "Rack: ";
                currentPlayer->printRack();
                char action;
                int tmp;
                if (dynamic_cast<Man*>(currentPlayer)) {
                    while(1){
                        bool anymove = false;
                        for (int i = 0 ; i < players.size() ; i++){
                            anymove = players[i]->anyMove() || anymove;
                        }
                        
                        if ((currentPlayer->rackSize() == 0 && game->bagSize() == 0) || anymove == false) {
                            if (!(currentPlayer->anyMove())) cout << "No more playable moves!" << endl;
                            if (currentPlayer->rackSize() == 0 && game->bagSize() == 0)
                                cout << "Empty rack and bag!" << endl;
                            else if (anymove == false)
                                cout << "All players have no possible moves!" << endl;
                            cout << "Game Over!" << endl;
                            cout << "Scoreboard: " << endl;
                            int tmp = 0;
                            for (int i = 0 ; i < players.size() ; i++) {
                                cout << "Player " << i+1 << "'s score: " << players[i]->getScore() << endl;
                                if (players[i]->getScore() > players[tmp]->getScore()) {
                                    tmp = i;
                                }
                            }
                            for (int i = 0 ; i < players.size() ; i++) {
                                if (players[tmp]->getScore() == players[i]->getScore() && tmp != i) {
                                    cout << "The game draws!" << endl;
                                    for (Player* player : players)
                                        delete player;
                                    delete game;
                                    return 0;
                                }
                            }
                            cout << "Player " << tmp+1 << " wins!" << endl;
                            for (Player* player : players)
                                delete player;
                            delete game;
                            return 0;
                        }
                        else if (currentPlayer->anyMove()){
                            cout << "Action (P/E/T): ";
                            tmp = 1;
                        }
                        else {
                            cout << "No more playable moves!" << endl;
                            cout << "Action (E/T): ";
                            tmp = 0;
                            
                        }
                        
                        cin >> action;
                        action = toupper(action);
                        if ((action != 'P' && action != 'E' && action != 'T') || (action == 'P' && tmp == 0)) {
                            cout << "Invalid input!" << endl;
                        }
                        else break;
                    }
                    if (action == 'P') {
                        currentPlayer->makeMove();
                    }
                    else if (action == 'E') {
                        cout << "Ended this turn!" << endl;
                        if (currentPlayer->rackSize() < R) {
                            currentPlayer->refillRack();
                            cout << "Rack refilled: ";
                            currentPlayer->printRack();
                        }
                        break;
                    }
                    
                    else if (action == 'T') {
                        bool anymove = false;
                        for (int i = 0 ; i < players.size() ; i++){
                            anymove = players[i]->anyMove() || anymove;
                        }
                        if ((currentPlayer->rackSize() == 0 && game->bagSize() == 0) || anymove == false) {
                            if (currentPlayer->rackSize() == 0 && game->bagSize() == 0)
                                cout << "Empty rack and bag!" << endl;
                            else if (anymove == false)
                                cout << "All players have no possible moves!" << endl;
                        }
                        cout << "Game Over!" << endl;
                        cout << "Scoreboard: " << endl;
                        int tmp = 0;
                        for (int i = 0 ; i < players.size() ; i++) {
                            cout << "Player " << i+1 << "'s score: " << players[i]->getScore() << endl;
                            if (players[i]->getScore() > players[tmp]->getScore()) {
                                tmp = i;
                            }
                        }
                        for (int i = 0 ; i < players.size() ; i++) {
                            if (players[tmp]->getScore() == players[i]->getScore() && tmp != i) {
                                cout << "The game draws!" << endl;
                                for (Player* player : players)
                                    delete player;
                                delete game;
                                return 0;
                            }
                        }
                        cout << "Player " << tmp+1 << " wins!" << endl;
                        for (Player* player : players)
                            delete player;
                        delete game;
                        return 0;
                }
            }
                else if (dynamic_cast<Bot*>(currentPlayer)) {
                    if (currentPlayer->anyMove()) {
                        currentPlayer->makeMove();
                    }
                    else {
                        cout << "No more playable moves!" << endl;
                        bool anymove = false;
                        for (int i = 0 ; i < players.size() ; i++){
                            anymove = players[i]->anyMove() || anymove;
                        }
                        if ((currentPlayer->rackSize() == 0 && game->bagSize() == 0) || anymove == false) {
                            if (currentPlayer->rackSize() == 0 && game->bagSize() == 0)
                                cout << "Empty rack and bag!" << endl;
                            else if (anymove == false)
                                cout << "All players have no possible moves!" << endl;
                            cout << "Game Over!" << endl;
                            cout << "Scoreboard: " << endl;
                            int tmp = 0;
                            for (int i = 0 ; i < players.size() ; i++) {
                                cout << "Player " << i+1 << "'s score: " << players[i]->getScore() << endl;
                                if (players[i]->getScore() > players[tmp]->getScore()) {
                                    tmp = i;
                                }
                            }
                            for (int i = 0 ; i < players.size() ; i++) {
                                if (players[tmp]->getScore() == players[i]->getScore() && tmp != i) {
                                    cout << "The game draws!" << endl;
                                    for (Player* player : players)
                                        delete player;
                                    delete game;
                                    return 0;
                                }
                            }
                            cout << "Player " << tmp+1 << " wins!" << endl;
                                for (Player* player : players)
                                    delete player;
                                delete game;
                                return 0;
                        }
                        else {
                            cout << "Ended this turn!" << endl;
                            if (currentPlayer->rackSize() < R) {
                                currentPlayer->refillRack();
                                cout << "Rack refilled: ";
                                currentPlayer->printRack();
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}
