#include <iostream>
#include <string>
#include "gamemap.h"
#include "character.h"

using namespace std;

int main(){
    cout << "Welcome to yet another board game! \n";
    cout << "This is a board game based on Starwars elements. \n";
    cout << "For detailed game rules, please read https://github.com/Sk3W3d/yet-another-board-game\n";
    cout << "This is a command-based game. You need to type in commands during your turn to play the game\n";
    cout << "Type help to view all commands. \n";
    cout << "Input player number: (no less than 2)";
    int player_num;
    cin >> player_num;
    vector<character> players (player_num);
    for (int i = 0; i < player_num; i++){
        cout << "What role does player no. " << (i+1) << " want to play? ";
        string role;
        // cin >> platers[i].role;
    }
    gamemap map;
    map.init_map();
    map.output_map();
    bool endgame = false;
    int round = 0;
    while(!endgame){
        round++;
        cout << "Round " << round << endl;
        for (int i = 0; i < player_num; i++){
            // cout << "Now it's " << players[i].role << "'s turn. ";

        }
    }
    return 0;
}