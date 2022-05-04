#include <iostream>
#include <string>
#include <fstream>
#include "gamemap.h"
#include "character.h"

#define WALL "\u2588\u2588"

using namespace std;

void display_on_map(){

}

int main(){
    cout << "Welcome to yet another board game! \n";
    cout << "This is a board game based on Starwars elements. \n";
    cout << "For detailed game rules, please read https://github.com/Sk3W3d/yet-another-board-game\n";
    cout << "This is a command-based game. You need to type in commands during your turn to play the game\n";
    cout << "Type help to view all commands. (after entering the game)\n";
    cout << "Start a new game or read a game? (type \"start\" or \"read\"): ";
    string gamestart;
    cin >> gamestart;
    int player_num, round;
    vector<character> players;
    gamemap map;
    map.init_map();

    if (gamestart == "read"){
        cout << "Read from which file? ";
        string file;
        cin >> file;
        ifstream fin;
        fin.open(file);
        if ( fin.fail() ){
            cout << "Error in file opening!" << endl;
        }
        // gamemap map;
        // map.init_map();
        fin >> player_num >> round;
        for (int i = 0; i < player_num; i++){
            string role;
            fin >> role;
            character new_character(role);
            int hp, x, y, poe, health_buff;
            new_character.set_hp(hp);
            new_character.set_pos(x, y);
            new_character.set_poe(poe);
            new_character.set_health_buff(health_buff);
            players.push_back(new_character);
        }

        fin.close();
    }
    else{
        cout << "Input player number: (no less than 2)";
        cin >> player_num;
        for (int i = 0; i < player_num; i++){
            cout << "What role does player no. " << (i+1) << " want to play? ";
            string role;
            character new_character(role);
            players.push_back(new_character);
        }
        // gamemap map;
        // map.init_map();
        map.output_map();

        int round = 0;
    }

    bool endgame = false;
    while(!endgame){
        round++;
        cout << "Round " << round << endl;
        for (int i = 0; i < player_num; i++){
            if (players[i].get_hp() <= 0) continue;
            cout << "Now it's " << players[i].get_role() << "'s turn. ";

            players[i].beginning_of_turn();
            
            string cmd_input;
            cin >> cmd_input;
            while (cmd_input != "end")
            {
                if (cmd_input == "move"){
                    /*
                    // coordinates input (reserved, not used)
                    cout << "Input the coordinates that you would like to move to\n"; 
                    int x, y;
                    cin >> x >> y;
                    // test whether can move

                    // update position
                    players[i].update_pos(x, y);
                    **/

                    // wasd input
                    string movement_wasd;
                    cin >> movement_wasd;

                    map.update_map(players[i].get_coordinates().x, players[i].get_coordinates().y, "");

                    int walked; bool hit_wall = false;
                    for (int i = 0; i < movement_wasd.length(); i++){
                        switch (movement_wasd[i])
                        {
                        case 'w':
                            if ((players[i].get_coordinates().y+1) < map.get_map_content().size()
                                && map.get_map_content()[players[i].get_coordinates().x][players[i].get_coordinates().y+1] != WALL){
                                players[i].update_pos(0, 1);
                                ++walked;
                                break;
                            }
                        
                        case 's':
                            if ((players[i].get_coordinates().y-1) >= 0
                                && map.get_map_content()[players[i].get_coordinates().x][players[i].get_coordinates().y-1] != WALL){
                                players[i].update_pos(0, -1);
                                ++walked;
                                break;
                            }

                        case 'a':
                            if ((players[i].get_coordinates().x-1) >= 0
                                && map.get_map_content()[players[i].get_coordinates().x-1][players[i].get_coordinates().y] != WALL){
                                players[i].update_pos(-1, 0);
                                ++walked;
                                break;
                            }

                        case 'd':
                            if ((players[i].get_coordinates().x+1) < map.get_map_content()[0].size()
                                && map.get_map_content()[players[i].get_coordinates().x+1][players[i].get_coordinates().y] != WALL){
                                players[i].update_pos(1, 0);
                                ++walked;
                                break;
                            }

                        default:
                            cout << "You hit the wall! \n";
                            hit_wall = true;
                            break;
                        }
                        if (hit_wall) break;
                    }

                    cout << "You walked " << walked << " steps.  Current position: \n";

                    map.update_map(players[i].get_coordinates().x, players[i].get_coordinates().y, players[i].get_symbol());
                    map.output_map();

                } else if (cmd_input == "attack")
                {
                    /* code */
                } else if (cmd_input == "status")
                {
                    players[i].display_status();
                } else if (cmd_input == "map")
                {
                    map.output_map();
                } else if (cmd_input == "save")
                {
                    ofstream fout;
                    fout.open("save.txt");
                    if ( fout.fail() ) {
                        cout << "Error in file opening!" << endl;
                        exit(1);
                    }
                    fout << player_num << " " << round << endl;

                    for (int i = 0; i < player_num; i++){
                        fout << players[i].get_role() << " " << players[i].get_hp() << " " << players[i].get_coordinates().x 
                            << " " << players[i].get_coordinates().y << " " << players[i].get_poe() << " " 
                            << players[i].get_health_buff() << endl;
                    }

                    fout.close();
                }
                
                
                
                cin >> cmd_input;
            }
            
        }

        int survival = 0;
        for (int i = 0; i < player_num; i++) survival += (players[i].get_hp() >= 0);
        if (survival == 1) endgame = true;
    }
    return 0;
}