#include <iostream>
#include <string>
#include "gamemap.h"
#include "character.h"

#define WALL "\u2588\u2588"

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
    vector<character> players;
    for (int i = 0; i < player_num; i++){
        cout << "What role does player no. " << (i+1) << " want to play? ";
        string role;
        character new_character(role);
        players.push_back(new_character);
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