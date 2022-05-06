#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "gamemap.h"
#include "character.h"

#define WALL "\u2588\u2588"

using namespace std;

// refresh map display contents
void refresh_map_display(gamemap map, vector<character> characters){
    for (int i = 0; i < map.get_map_content().size(); i++){
        for (int j = 0; j < map.get_map_content()[0].size(); j++){
            for (int k = 0; k < characters.size(); k++){
                if (map.get_map_content()[i][j] == characters[k].get_symbol()){
                    map.update_map(i, j, "");
                }
            }                    
        }
    }
    
    for (int k = 0; k < characters.size(); k++){
        if (characters[k].get_hp()){
            map.update_map(20-characters[k].get_coordinates().y, characters[k].get_coordinates().x-1, characters[k].get_symbol());
        }
    }

    map.output_map();
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
            int hp, x, y, poe, health_buff, shield_buff;
            fin >> hp >> x >> y >> poe >> health_buff >> shield_buff;
            new_character.set_hp(hp);
            new_character.set_pos(x, y);
            new_character.set_poe(poe);
            new_character.set_health_buff(health_buff);
            new_character.set_shield_buff(shield_buff);
            new_character.update_hp(0);
            players.push_back(new_character);
        }

        fin.close();
    }
    else{
        // start a new game
        cout << "Input player number: (no less than 2)";
        cout << "Valid characters include {\"LukeSkywalker\", \"HanSolo\", \"Obi-wanKenobi\", \"R2D2\", \"Chewbacca\", "
            << "\"DarthVader\", \"JangoFett\", \"TuskenRaider\", \"DarthMaul\", \"DarthSidious\"}\n";
        const string roles[] = {"LukeSkywalker", "HanSolo", "Obi-wanKenobi", "R2D2", "Chewbacca", 
            "DarthVader", "JangoFett", "TuskenRaider", "DarthMaul", "DarthSidious"};
        string player_num_str;
        cin >> player_num_str;
        player_num = atoi(player_num_str.c_str());
        while (player_num < 2 && player_num > 10)
        {
            cout << "Invalid player number. Please input a number from 2 to 10. \n";
        }
        
        for (int i = 0; i < player_num; i++){
            cout << "What role does player no. " << (i+1) << " want to play? (input full name)";
            string role;
            role_input: cin >> role;
            bool role_exist = false;
            for (int j = 0; j < role.size(); j++)
            {
                if (role == roles[j]) role_exist = true;
            }
            if (!role_exist) goto role_input;
            character new_character(role);
            players.push_back(new_character);
        }
        // gamemap map;
        // map.init_map();
        map.output_map();

        round = 0;
    }

    bool endgame = false;
    while(!endgame){
        round++;
        map.element_gen(round);
        refresh_map_display(map, players);
        cout << "Round " << round << endl;
        for (int i = 0; i < player_num; i++){
            if (players[i].get_hp() <= 0) continue;
            cout << "Now it's " << players[i].get_role() << "'s turn. ";

            players[i].beginning_of_turn();
            
            string cmd_input;
            cin >> cmd_input;
            while (cmd_input != "end")
            {
                if (cmd_input == "help"){
                    cout << "The main commands include: move, skill, map, status, and save. You may enter these commands and the detailed instruction will be shown. \n";
                    cout << "Input exit as command to exit the game. \n";
                }
                else if (cmd_input == "move"){
                    // RELATIVE COORDINATES INPUT
                    cout << "Please input the relative coordinates of the position you want to move to: (2 integers)";
                    int x, y;
                    cin >> x >> y;
                    if ((players[i].get_coordinates().x + x) <= 0 || (players[i].get_coordinates().x + x) > map.get_map_content()[0].size()
                        || (players[i].get_coordinates().y + y) <= 0 || (players[i].get_coordinates().y + y) > map.get_map_content().size())
                    {
                        cout << "You are moving out of map. Invalid input. \n";
                        // cin >> cmd_input;
                        continue;
                    }
                    Point destination = {players[i].get_coordinates().x + x, players[i].get_coordinates().y + y};
                    cout << "Destination: " << destination.x << ", " << destination.y << endl;
                    Point intercept;
                    if (penetrate_se(players[i].get_coordinates(), destination, map.get_map_content(), intercept)){
                        players[i].set_poe(players[i].get_poe() - players[i].get_mass() * distance_pp(players[i].get_coordinates(), destination));
                        players[i].set_pos(destination.x, destination.y);
                        cout << "Movement successful. Current position: " << destination.x << ", " << destination.y << endl;
                        cout << "Remaining POE: " << players[i].get_poe() << endl;
                    } else {
                        cout << "Movement unsucessful. You hit the wall. Current position: " << intercept.x << ", " << intercept.y << endl;
                        players[i].set_poe(players[i].get_poe() - players[i].get_mass() * distance_pp(players[i].get_coordinates(), intercept));
                        players[i].set_pos(intercept.x, intercept.y);
                        cout << "Remaining POE: " << players[i].get_poe() << endl;
                    }
                    refresh_map_display(map, players);


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

                    /*
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

                    **/



                } else if (cmd_input == "skill")
                {
                    Point intercept;
                    if (players[i].get_role() == "LukeSkywalker"){
                        cout << "You have 1 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            LukeSkywalker_1(players, map.get_map_content(), intercept);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "HanSolo")
                    {
                        cout << "You have 2 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            HanSolo_1(players, map.get_map_content(), intercept);
                        } else if (skill == "2")
                        {
                            HanSolo_2(players);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "Obi-wanKenobi")
                    {
                        cout << "You have 2 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            ObiwanKenobi_1(players, map.get_map_content(), intercept);
                        } else if (skill == "2")
                        {
                            ObiwanKenobi_2(map.get_map_content(), players, 30);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "R2D2")
                    {
                        cout << "You have 2 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            R2D2_1(map.get_map_content(), players);
                        } else if (skill == "2")
                        {
                            R2D2_2(map.get_map_content(), players);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "Chewbacca")
                    {
                        cout << "You have 2 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            Chewbacca_1(map.get_map_content(), players, intercept);
                        } else if (skill == "2")
                        {
                            Chewbacca_2(map.get_map_content(), players, intercept);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "DarthVader")
                    {
                        cout << "You have 2 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            DarthVader_1(map.get_map_content(), players, intercept);
                        } else if (skill == "2")
                        {
                            DarthVader_2(map.get_map_content(), players, intercept);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "JangoFett")
                    {
                        cout << "You have 1 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            JangoFett_1(map.get_map_content(), players, intercept);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "TuskenRaider")
                    {
                        cout << "You have 2 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            TuskenRaider_1(map.get_map_content(), players);
                        } else if (skill == "2")
                        {
                            TuskenRaider_2(players);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "DarthMaul")
                    {
                        cout << "You have 1 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            DarthMaul_1(map.get_map_content(), players, intercept);
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    } else if (players[i].get_role() == "DarthSidious")
                    {
                        cout << "You have 2 skill. Please confirm which skill you would like to use. (input skill no. to execute, other inputs to abort. ): ";
                        string skill;
                        cin >> skill;
                        if (skill == "1"){
                            // DarthSidious_1(map.get_map_content(), players, );
                        } else if (skill == "2")
                        {
                            // DarthSidious_2();
                        } else {
                            cout << "You aborted using skill. Please re-enter command. \n";
                        }
                    }
                    
                    
                    
                } else if (cmd_input == "status")
                {
                    players[i].display_status();
                } else if (cmd_input == "map")
                {
                    map.output_map();
                    refresh_map_display(map, players);
                } else if (cmd_input == "save")
                {
                    cout << "Where would you like to save the game? Please input the file name. \n";
                    string file_save;
                    cin >> file_save;
                    ofstream fout;
                    fout.open(file_save);
                    if ( fout.fail() ) {
                        cout << "Error in file opening! Please re-enter the command. " << endl;
                        continue;
                    }
                    fout << player_num << " " << round << endl;

                    for (int i = 0; i < player_num; i++){
                        fout << players[i].get_role() << " " << players[i].get_hp() << " " << players[i].get_coordinates().x 
                            << " " << players[i].get_coordinates().y << " " << players[i].get_poe() << " " 
                            << players[i].get_health_buff() << " " << players[i].get_shield_buff() << endl;
                    }

                    fout.close();
                    cout << "Game saved successfully. \n";
                } else if (cmd_input == "exit")
                {
                    return 0;
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