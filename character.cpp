// character.cpp
#include <string>
#include <cstring>
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include "character.h"
#include "gamemap.h"

#define WALL "\u2588\u2588"

using namespace std;

character::character(std::string role){
    coordinates = {0, 0};
    this->role = role;
    poe = 0;
    health_buff = 0;
    shield_buff = 0;
    life = true;
    if (role == "LukeSkywalker"){ 
        hp = 480;
        max_poe = 40;
        mass = 0.8;
        symbol = "\uA19C";
        coordinates = {4, 5};
        damage = 95;
        distance = 5;
        penetrate = false;
        control = false;
        inward = false;
        control_distance = 0;
    } else if (role == "HanSolo")
    {
        hp = 480;
        max_poe = 55;
        mass = 1;
        symbol = "\uA167";
        coordinates = {4, 10};
        damage = 90;
        distance = 5; // will not be visited
        penetrate = false;
        control = false;
        inward = false;
        control_distance = 0;
    } else if (role == "Obi-wanKenobi")
    {
        hp = 580;
        max_poe = 60;
        mass = 1.2;
        symbol = "\uA010";
        coordinates = {4, 15};
        damage = 70;
        distance = 6; 
        penetrate = true;
        control = false;
        inward = false;
        control_distance = 0;
    } else if (role == "R2D2")
    {
        hp = 580;
        max_poe = 60;
        mass = 1.2;
        symbol = "\uA269";
        coordinates = {8, 5};
        damage = 120;
        distance = 3; 
        penetrate = true;
        control = false;
        inward = false;
        control_distance = 0;
    } else if (role == "Chewbacca")
    {
        hp = 800;
        max_poe = 100;
        mass = 2;
        symbol = "\uA12C";
        coordinates = {8, 10};
        damage = 125;
        distance = 2; 
        penetrate = true;
        control = false;
        inward = false;
        control_distance = 0;
    } else if (role == "DarthVader")
    {
        hp = 480;
        max_poe = 50;
        mass = 1.1;
        symbol = "\uA111";
        coordinates = {8, 15};
        damage = 30;
        distance = 4; 
        penetrate = true;
        control = true;
        inward = false;
        control_distance = 5;
    } else if (role == "JangoFett")
    {
        hp = 400;
        max_poe = 35;
        mass = 0.9;
        symbol = "\uA007";
        coordinates = {12, 8};
    } else if (role == "TuskenRaider")
    {
        hp = 300;
        max_poe = 30;
        mass = 1.5;
        symbol = "\uA233";
        coordinates = {12, 15};
    } else if (role == "DarthMaul")
    {
        hp = 340;
        max_poe = 40;
        mass = 1;
        symbol = "\uA389";
        coordinates = {38, 10};
        damage = 80;
        distance = 6; 
        penetrate = false;
        control = false;
        inward = false;
        control_distance = 0;
    } else if (role == "DarthSidious")
    {
        hp = 520;
        max_poe = 75;
        mass = 1.5;
        symbol = "\uA421";
        coordinates = {38, 15};
    }
    
    
}

int character::poe_gen(){
    srand(time(0));
    int roll = rand()%6 + 1;
    std::cout << "You rolled " << roll << "! \n";
    poe = std::min(max_poe, poe+roll);
    std::cout << "You now have POE of " << poe << ". \n";
}

void character::beginning_of_turn(){
    poe_gen();
    if (health_buff > 0){
        update_hp(50);
        health_buff--;
    }
    display_status();
}

void character::display_status(){
    std::cout << "Current status: \n";
    std::cout << "Hp: " << hp << std::endl;
    std::cout << "POE: " << poe << std::endl;
    std::cout << "Buff status: \nHealth buff: " << health_buff << std::endl << "Shield buff: " << shield_buff << std::endl;
}



double min_distance(double x, double y, vector<vector<string>> map_content) {
    //find the distance of point(x, y) to the nearest wall.
    double result = 1000;
    for (int i = 0; i < 20; i++) {
        for(int j = 0; j < 40; j++) {
            //for map_content[i][j], its x == j + 1, y == 20 - i .
            if (map_content[i][j] == WALL) {
                result = min(result, sqrt(pow(j + 1 - x, 2) + pow(20 - i - y, 2)));
            }
        }
    }
    return result;
}


double distance_pl(Point x, Point a, Point b) {
    //distance from Point x to line ab
    double A = b.y - a.y;
    double B = b.x - a.x;
    double C = a.y * (b.x - a.x) - a.x * (b.y - a.y);
    return abs(A * x.x + B * x.y + C) / sqrt(A * A + B * B);
}

double distance_pp(Point x, Point y) {
    //distance form Point x and y
    return sqrt(pow(y.x - x.x, 2) + pow(y.y - x.y, 2));
}


bool penetrate_se(Point start, Point end, vector<vector<string>> map_content, Point &intercept) {
    //se: given start Point and end Point
    if (start.x == end.x && start.y == end.y) {
        return true;
    }
    else if (start.x == end.x) {
        intercept.x = start.x;        
        for (int i = start.y; i != end.y+ abs(end.y - start.y)/(end.y - start.y); i += abs(end.y - start.y)/(end.y - start.y)) {
            if (map_content[20 - i][start.x - 1] == WALL){
                intercept.y = end.y > start.y ? i - 1 : i + 1;
                return false;
            }
        }
        intercept.y = end.y;
        return true;
    }
    else if (start.y == end.y) {
        intercept.y = start.y;
        for (int i = start.x; i != end.x+ abs(end.x - start.x)/(end.x - start.x); i += abs(end.x - start.x)/(end.x - start.x)) {
            if (map_content[20 - start.y][i - 1] == WALL) {
                intercept.x = end.x > start.x ? i - 1 : i + 1;
                return false;
            }
        }
        intercept.x = end.x;
        return true;
    }
    else {
        double intersection[58][2];
        int index = 0;
        double dx = end.x > start.x ? 0.5 : -0.5;
        double dy = end.y > start.y ? 0.5 : -0.5;
        for (int i = start.x; i != end.x; i += (abs(end.x - start.x)) / (end.x - start.x)) {
            //x-coordinate of intersection is i+0.5 (intersection on vertical lines)
            intersection[index][0] = i + dx , intersection[index][1] = start.y + (double(end.y - start.y) / double(end.x - start.x)) * double(i + dx - start.x);
            index++;
        }
        for (int j = start.y; j != end.y; j += (abs(end.y - start.y)) / (end.y - start.y)) {
            //y-coordinate of intersection is j+0.5 (intersections on horizontal lines)
            intersection[index][0] = start.x + (double(end.x - start.x) / double(end.y - start.y)) * double(j + dy - start.y) , intersection[index][1] = j + dy;
            index++;
        }
        //the 2 "for" loops above: add all intersections of the line start-end and the map gridding to the array.
        index--;
        for (int i = 0; i <= index - 1; i++) {
            for (int j = 0; j <= index - 1 - i; j++) {
                double x1 = intersection[j][0], y1 = intersection[j][1], 
                    x2 = intersection[j + 1][0], y2 = intersection[j + 1][1];
                if ((pow(x1 - start.x, 2) + pow(y1 - start.y, 2)) > (pow(x2 - start.x, 2) + pow(y2 - start.y, 2))) {
                    double temp[2] = {intersection[j][0], intersection[j][1]};
                    intersection[j][0] = intersection[j + 1][0], intersection[j][1] = intersection[j + 1][1];
                    intersection[j + 1][0] = temp[0], intersection[j + 1][1] = temp[1];
                    // swap(intersection[j], intersection[j+1]);
                }
            }
            //nested loop above: sort the intersection Points in the array by their distance to the start Point. 
        }
        for (int t = 0; t <= index; t++) {
            if (min_distance(intersection[t][0], intersection[t][1], map_content) <= 0.72){ //slightly larger the sqrt(1/2)
                intercept.x = round(intersection[t][0] - dx);
                intercept.y = round(intersection[t][1] - dy);
                //intercept: the pixel at which the controlled character's movement is stopped by wall.
                return false;
            }
        }
        intercept.x = end.x;
        intercept.y = end.y;
        return true;
    }
}


bool penetrate_sd(character controller, Point start, Point direction, int distance, vector<vector<string>> map_content, Point& intercept) {
    //sd: given start Point, distance and direction
    //note: only controlling skills call this function
    int dx = round((distance / distance_pp(direction, start)) * (direction.x - start.x));
    int dy = round((distance / distance_pp(direction, start)) * (direction.y - start.y));
    Point end;
    end.x = (start.x + dx <= 40 && start.x + dx >= 0) ? start.x + dx : (start.x + dx > 40 ? 40 : 0);
    end.y = (start.y + dy <= 20 && start.x + dx >= 0) ? start.x + dx : (start.x + dx > 20 ? 20 : 0);
    if ((end.x - controller.get_coordinates().x) * (start.x - controller.get_coordinates().x) < 0) {
        end.x = controller.get_coordinates().x + (start.x == controller.get_coordinates().x ? 0 : abs(start.x - controller.get_coordinates().x) / (start.x - controller.get_coordinates().x));
        end.y = controller.get_coordinates().y + (start.y == controller.get_coordinates().y ? 0 : abs(start.y - controller.get_coordinates().y) / (start.y - controller.get_coordinates().y));
    }
    return penetrate_se(start, end, map_content, intercept);
}

int search(string name, vector<character> living) {
    for (int i = 0; i < living.size(); i++) {
        if (living[i].get_role() == name) {
            return i;
        }
    }
}

void aoe(character attacker, vector<character> &living, int poe_comsume, vector<vector<string>> &map_content, Point &intercept) {
    int count = 0;
    if (attacker.get_poe() >= poe_comsume) {
        for (int i = 0; i < living.size(); i++) {
            if (living[i].life && ((attacker.penetrate || penetrate_se(attacker.get_coordinates(), living[i].get_coordinates(), map_content, intercept))
                && distance_pp(attacker.get_coordinates(), living[i].get_coordinates()) <= attacker.distance && attacker.get_role() != living[i].get_role())) {
                living[i].update_hp(-attacker.damage);
                //damage(attacker.damage, i, living);
                cout << living[i].get_role() << " HP- " << attacker.damage << " and is now " << living[i].get_hp() << endl;
                count += 1;
                if (attacker.control) {
                    Point situation_1 = {attacker.get_coordinates().x - living[i].get_coordinates().x, attacker.get_coordinates().y - living[i].get_coordinates().y};
                    Point situation_2 = {-attacker.get_coordinates().x + living[i].get_coordinates().x, -attacker.get_coordinates().y + living[i].get_coordinates().y};
                    Point direction = attacker.inward ? situation_1 : situation_2;
                    bool stopped = !penetrate_sd(attacker, living[i].get_coordinates(), direction, attacker.control_distance, map_content, intercept);
                    living[i].set_pos(intercept.x, intercept.y);
                    cout << living[i].get_role() << " has been moved to (" << living[i].get_coordinates().x << ", " << living[i].get_coordinates().y << ") \n";
                    if (attacker.get_role() == "DarthVader" && stopped) {
                        living[i].update_hp(-120);
                        cout << living[i].get_role() << " hit wall. additional damage is dealt. his HP is now:" << living[i].get_hp() << endl;
                    }
                }
            }
        }
        if (count == 0) {
            cout << "seems like no one was damaged ! \n";
        }
        else if (attacker.get_role() == "Obi-wanKenobi") {
            living[search("Obi-wanKenobi", living)].update_hp(40 * (count - 1));
            cout << count << " enemies was hit. Obiwan recovers HP of " << 40 * (count - 1);
        }
    }
    else {
        cout << "your POE (points of energy) is not enough! \n";
    }

}

void LukeSkywalker_1(vector<character> &living, vector<vector<string>> &map_content, Point &intercept) {
    int index = search("LukeSkywalker", living);
    if (living[index].get_poe() >= 12){
        aoe(living[index], living, 12, map_content, intercept);
        living[index].consume_poe(12);
        cout << "your POE (points of energy) now:" << living[index].get_poe() << endl;
    }
    else{
        cout << "Your POE (points of energy) is not enough!" << endl;
    }
}

void HanSolo_1(vector<character> &living, vector<vector<string>> &map_content, Point &intercept) {
    cout << "wanna hit an enemy or give up this attack? \n";
    cout << "input e/g  \n";
    char command;
    cin >> command;
    if (command == 'e') {
        cout << "possible choices: ";
        for (int i = 0; i < living.size(); i++) {
            if ((living[i].get_role() != "HanSolo") && living[i].life) {
                cout << i << ":" << living[i].get_role() << "    ";
            }
        }
        cout << endl << "enter your choice: ";
        char choice[50];
        cin >> choice;
        while (!strlen(choice)==1 || !isdigit(choice[0]) || (isdigit(choice[0]) && (choice[0] < '0' || choice[0] >= '0'+living.size())) || !living[atoi(choice)].life || living[atoi(choice)].get_role() == "HanSolo") {
            cout << endl << "please enter a valid choice!";
            cin >> choice;
        }
    LABEL1: if (!penetrate_se(living[search("HanSolo", living)].get_coordinates(), living[atoi(choice)].get_coordinates(), map_content, intercept)) {
        cout << "your attack cannot penetrate walls! \n";
        cout << "please input your choice again or input 'g' to give up attacking :";
        cin >> choice;
        while (!strlen(choice)==1 || choice[0] != 'g' && (!isdigit(choice[0]) || (isdigit(choice[0]) && (choice[0] >= '0'+living.size())) || !living[atoi(choice)].life || living[atoi(choice)].get_role() == "HanSolo")) {
            cout << "please enter a valid command!";
            cin >> choice;
        }
        if (choice[0] != 'g') {
            goto LABEL1;
        }
        else {
            goto LABEL2;
        }
    }
    else {
        if (living[search("HanSolo", living)].get_poe() < 12) {
            cout << "your POE (points of energy) is not enough! \n";
            goto LABEL2;
        }
        else {
            living[atoi(choice)].update_hp(-living[search("HanSolo", living)].damage);
            living[search("HanSolo", living)].consume_poe(12);
            cout << living[atoi(choice)].get_role() << " HP-" << living[search("HanSolo", living)].damage << " and is now" << living[atoi(choice)].get_hp() << endl;
            cout << "your POE:" << living[search("HanSolo", living)].get_poe() << endl;
        }
    }
    }
    else {
    LABEL2: cout << "attack aborted \n";
    }
}

void HanSolo_2(vector<character> &living) {
    cout << "wanna interchange position with someone or give up this sttempt? \n";
    cout << "input 'i' to interchange or any character else to give up attempt \n";
    char command;
    cin >> command;
    if (command == 'i') {
        cout << "possible choices: ";
        for (int i = 0; i < living.size(); i++) {
            if ((living[i].get_role() != "HanSolo") && living[i].life) {
                cout << i << ":" << living[i].get_role();
            }
        }
        cout << endl << "enter your choice: ";
        char choice;
        cin >> choice;
        while (!isdigit(choice) || (isdigit(choice) && (choice <= 0 || choice >= living.size())) || !living[atoi(&choice)].life || living[atoi(&choice)].get_role() == "HanSolo") {
            cout << "please enter a valid choice, or input 'g' to give up";
            cin >> choice;
            if (choice == 'g') {
                cout << "attempt aborted! \n";
                return;
            }
        }
        if (living[search("HanSolo", living)].get_poe() >= 15) {
            Point copy = living[search("HanSolo", living)].get_coordinates();
            living[search("HanSolo", living)].set_pos(living[choice].get_coordinates().x, living[choice].get_coordinates().y);
            living[choice].set_pos(copy.x, copy.y);
            living[search("HanSolo", living)].consume_poe(15);
            cout << "success!" << endl << "now your POE is " << living[search("HanSolo", living)].get_poe();
        }
        else {
            cout << "your POE (points of energy) is not enough!" << endl;
            cout << "attempt aborted!" << endl;
        }
    }
    else {
        cout << "attempt aborted! \n";
    }
}

void ObiwanKenobi_1(vector<character> &living, vector<vector<string>> &map_content, Point &intercept) {
    if (living[search("Obi-wanKenobi", living)].get_poe() >= 10){
        aoe(living[search("Obi-wanKenobi", living)], living, 10, map_content, intercept);
        living[search("Obi-wanKenobi", living)].consume_poe(10);
        cout << "\nYour POE (points of energy) now: " << living[search("Obi-wanKenobi", living)].get_poe() << endl;
    }
    else{
        cout << "Your POE (point sof energy) is not enough!" << endl;
    }
}

void ObiwanKenobi_2(vector<vector<string>> &map_content, vector<character> &living, int poe_consumption) {
    Point location = { 0, 0 }, minimum;
    if (living[search("Obi-wanKenobi", living)].get_poe() >= poe_consumption) {
        int distance = 1000;
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 39; j++) {
                if (map_content[i][j] == "\u002B ") {
                    location.x = j + 1;
                    location.y = 20 - i;
                    if (distance > distance_pp(location, living[search("Obi-wanKennobi", living)].get_coordinates())){
                        minimum.x = location.x; minimum.y = location.y;
                        distance = distance_pp(location, living[search("Obi-wanKennobi", living)].get_coordinates());                    
                    }
                }
            }
        }
        if (distance == 1000) {
            cout << " there is no health buff in the map! \n";
        }
        else {
            int i = 20 - minimum.y;
            int j = minimum.x - 1;
            map_content[i][j] = "";
            living[search("Obi-wanKenobi", living)].set_health_buff(1);
            living[search("Obi-wanKenobi", living)].consume_poe(20);
            cout << "buff get. Now your POE is " << living[search("Obi-wanKenobi", living)].get_poe();
        }
    }
    else {
        cout << "your POE (points of energy) is not enough!  \n";
    }
}

void R2D2_1(vector<vector<string>> &map_content, vector<character> &living ) {
    int count = 0;
    if (living[search("R2D2", living)].get_poe() >= 18) {
        for (int i = 0; i < living.size(); i++) {
            if (min_distance(living[i].life && living[i].get_coordinates().x, living[i].get_coordinates().y, map_content) <= 3 && living[i].get_role() != "R2D2") {
                living[i].update_hp(-120);
                cout << living[i].get_role() << " is attacked. his HP now: " << living[i].get_hp();
                count += 1;
            }
        }
    }
    else {
        cout << "your POE (points of energy) is not enough! " << endl;
        return;
    }
    if (count) {
        living[search("R2D2", living)].consume_poe(18);
        cout << "Your current POE (points of energy): " << living[search("R2D2", living)].get_poe();
    }
}

void R2D2_2(vector<vector<string>> &map_content, vector<character> &living) {
    if (living[search("R2D2", living)].get_coordinates().y == map_content.size()) {
        cout << "you can not place wall out of the map!" << endl;
        return;
    }
    else {
        if (living[search("R2D2", living)].get_poe() < 3) {
            cout << "your POE (points of energy) is not enough!" << endl;
        }
        else {
            int i = 19 - living[search("R2D2", living)].get_coordinates().y;
            int j = living[search("R2D2", living)].get_coordinates().x - 1;
            //map_content[i][j]: cell to contruct the wall
            if (map_content[i][j] != "") {
                cout << "you can only place wall at empty cell ! \n";
            }
            else {
                map_content[i][j] = "\u2588\u2588";
                living[search("R2D2", living)].consume_poe(3);
                cout << "success! now your POE (points of energy) is: " << living[search("R2D2", living)].get_poe() << endl;
            }
        }
    }
}

void Chewbacca_1(vector<vector<string>> &map_content, vector<character> &living, Point &intercept) {
    aoe(living[search("Chewbacca", living)], living, -8, map_content, intercept);
    living[search("Chewbacca", living)].consume_poe(-8);
    std::cout << "your POE (points of energy) is now: " << living[search("Chewbacca", living)].get_poe() << endl;
}

void Chewbacca_2(vector<vector<string>> &map_content, vector<character> &living, Point &intercept) {
    if (living[search("Chewbacca", living)].get_poe() < 25) {
        cout << "your POE is not enough for this! " << endl;
        return;
    }
    else {
        if (living[search("Chewbacca", living)].get_hp() < 180) {
            cout << "your HP has to be more than 180 to do this!";
        }
        for (int i = 0; i < living.size(); i++) {
            if (living[i].life && distance_pp(living[search("Chewbacca", living)].get_coordinates(), living[i].get_coordinates()) <= 8 && living[i].get_role() != "Chewbacca") {
                Point direction = { living[search("Chewbacca", living)].get_coordinates().x - living[i].get_coordinates().x, living[search("Chewbacca", living)].get_coordinates().y - living[i].get_coordinates().y };
                    penetrate_sd(living[search("Chewbacca", living)], living[search("Chewbacca", living)].get_coordinates(), direction, living[search("Chewbacca", living)].control_distance, map_content, intercept);
                    living[i].set_pos(intercept.x, intercept.y);
                    living[i].set_poe(0);
                    cout << living[i].get_role() << " moved to ( " << living[i].get_coordinates().x << ", " << living[i].get_coordinates().y << "), and POE reset. \n";
            }
        }
        living[search("Chewbacca", living)].consume_poe(25);
            cout << " your current POE (points of energy) is :" << living[search("Chewbacca", living)].get_poe();
    }
}

void DarthVader_1(vector<vector<string>> &map_content, vector<character> &living, Point &intercept) {
    if (living[search("DarthVader", living)].get_poe() < 25) {
        cout << "YOUR POE(points of enregy is not enough! " << endl;
        return;
    }
    else {
        aoe(living[search("DarthVader", living)], living, 25, map_content, intercept);
        living[search("DarthVader", living)].consume_poe(25);
        cout << "your current poe: " << living[search("DarthVader", living)].get_poe() << endl;
    }
}

void DarthVader_2(vector<vector<string>> &map_content, vector<character> &living, Point &intercept) {
    if (living[search("DarthVader", living)].get_poe() < 10) {
        cout << "your POE is not enough for this! " << endl;
        return;
    }
    else {
        for (int i = 0; i < living.size(); i++) {
            if (living[i].life && distance_pp(living[search("DarthVader", living)].get_coordinates(), living[i].get_coordinates()) <= 10 && living[i].get_role() != "DarthVaader") {
                Point direction = { living[search("DarthVader", living)].get_coordinates().x - living[i].get_coordinates().x, living[search("DarthVader", living)].get_coordinates().y - living[i].get_coordinates().y };
                    penetrate_sd(living[search("DarthVader", living)], living[search("DarthVader", living)].get_coordinates(), direction, living[search("DarthVader", living)].control_distance, map_content, intercept);
                    living[i].set_pos(intercept.x, intercept.y);
                    cout << living[i].get_role() << " moved to ( " << living[i].get_coordinates().x << ", " << living[i].get_coordinates().y << ") \n";
            }
        }
        living[search("DarthVader", living)].consume_poe(10);
            cout << " your current POE (points of energy) is :" << living[search("DarthVader", living)].get_poe() << endl;
    }
}

void JangoFett_1(vector<vector<string>> &map_content, vector<character> &living, Point &intercept) {
    if (living[search("JangoFett", living)].get_poe() < 13) {
        cout << "your POE (points of energy) is not enough !" << endl;
        return;
    }
    else {
        Point direction;
        string raw;
        cout << "input a direction (two integer split by space). \n";
        cout << " example: input '1 1' to indecate the direction towards 45 degrees to the upper right. \n";
        char x, y;
        cin >> x, y;
        while (!isdigit(x) || !isdigit(y) || (x == 0 && y == 0)) {
            cout << "please input a valid value!" << endl;
            cin >> x, y;
        }
        direction.x = x;
        direction.y = y;
        cin >> raw;
        bool available = true;
        char a[100000];
        strcpy(a, raw.c_str());
        for (int i = 0; i < raw.size(); i++) {
            if (!isdigit(a[i])) {
                available = false;
            }
        }
        while (!available) {
            cout << "please input a valid value! " << endl;
            available = true;
            cin >> raw;
            strcpy(a, raw.c_str());
            for (int i = 0; i < raw.size(); i++) {
                if (!isdigit(a[i])) {
                    available = false;
                }
            }
        }
        int distance = min(atoi(raw.c_str()), 10);

        penetrate_sd(living[search("JangoFett", living)], living[search("JangoFett", living)].get_coordinates(), direction, distance, map_content, intercept);
        Point explosion = intercept;
        cout << "missile exploded at ( " << explosion.x << ", " << explosion.y << "). \n";
        for (int i = 0; i < map_content.size(); i++) {
            for (int j = 0; j < 40; j++) {
                if (map_content[i][j] == "\u2588\u2588") {
                    Point wall = { j + 1, 20 - 1 };
                    if (distance_pp(explosion, wall) <= 4) {
                        map_content[i][j] = "";
                        cout << "wall at ( " << wall.x << ", " << wall.y << ") is cleared. \n";
                    }
                }
            }
        }
        for (int i = 0; i < living.size(); i++) {
            if (living[i].life && living[i].get_role() != "JangoFett" && distance_pp(explosion, living[i].get_coordinates()) <= 4) {
                living[i].update_hp(-95);
                cout << living[i].get_role() << " HP -= 95 and is now " << living[i].get_hp() << endl;
            }
        }
        living[search("JangoFett", living)].consume_poe(13);
        cout << "your current POE(point sof energy): " << living[search("JangoFett", living)].get_poe();
    }
}

void TuskenRaider_1(vector<vector<string>> &map_content, vector<character> &living) {
    if (living[search("TuskenRaider", living)].get_poe() < 5) {
        cout << "your POE (points of energy) is not enough !" << endl;
        return;
    }
    else {
        cout << "possible choices: ";
        for (int i = 0; i < living.size(); i++) {
            if ((living[i].get_role() != "TuskenRaider") && living[i].life) {
                cout << i << ":" << living[i].get_role() << ";  ";
            }
        }
        cout << endl << "enter your choice: ";
        char choice;
        cin >> choice;
        while (!isdigit(choice) || (isdigit(choice) && (choice <= 0 || choice >= living.size())) || !living[atoi(&choice)].life || living[atoi(&choice)].get_role() == "JangoFett") {
            cout << endl << "please enter a valid choice!";
            cin >> choice;
        }
        int index = atoi(&choice);
        int miss = rand() % 2;
        if (miss) {
            cout << "Oops! you missed! \n";
            return;
        }
        else {
            living[index].update_hp(-65);
            cout << living[index].get_role() << " is hit, his HP -= 65 and is now " << living[index].get_hp() << endl;
        }
    }
}

void TuskenRaider_2(vector<character> &living) {
    if (living[search("TuskenRaider", living)].get_poe() < 5) {
        cout << "your POE (points of energy) is not enough !" << endl;
        return;
    }
    else {
        for (int i = 0; i < living.size(); i++) {
            if ((living[i].get_role() != "TuskenRaider") && living[i].life && distance_pp(living[search("TuskenRaider", living)].get_coordinates(), living[i].get_coordinates()) <= 4) {
                living[i].update_hp(-70);
                living[search("TuskenRaider", living)].update_hp(70);
                cout << living[i].get_role() << " is dealt 70 damage and it's absorbed by you. " << living[i].get_role() << "'s HP now:" << living[i].get_hp() << endl;
            }
            cout << "Your HP now: " << living[search("TuskenRaider", living)].get_hp() << endl;
        }
    }
}

void DarthMaul_1(vector<vector<string>> &map_content, vector<character> &living, Point &intercept) {
    int index = search("DarthMaul", living);
    if (living[index].get_poe() < 11) {
        cout << "your POE (points of energy) is not enough!" << endl;
        return;
    }
    else {
        aoe(living[index], living, 11, map_content, intercept);
        living[index].consume_poe(11);
        cout << "your POE (points of energy) now:" << living[index].get_poe() << endl;
        cout << "wanna use additional move?   input y/n: ";
        char cmd;
        cin >> cmd;
        while (cmd != 'y' && cmd != 'n') {
            cout << endl << "please input y/n! input again: ";
            cin >> cmd;
        }
        if (cmd == 'y') {
            cout << "input a direction (two integer split by space). \n";
            cout << " example: input '1 -1' to indecate the direction towards 45 degrees to the lower right. \n";
            char x, y;
            cin >> x, y;
            while (!isdigit(x) || !isdigit(y) || (x == 0 && y == 0)) {
                cout << "please input a valid value!" << endl;
                cin >> x, y;
            }
            Point direction;
            direction.x = round((5 / (pow(x, 2) + pow(y, 2))) * x);
            direction.y = round((5 / (pow(x, 2) + pow(y, 2))) * y);
            int current_x = living[index].get_coordinates().x + direction.x;
            int current_y = living[index].get_coordinates().y + direction.y;
            if (current_x <= 0 || current_x > 40 || current_y <= 0 || current_y >= 20) {
                cout << "you cannot be out of map! movement aborted \n";
                return;
            }
            else {
                living[index].set_pos(current_x, current_y);
            }
        }
        else {
            cout << "movement aborted \n";
            return;
        }
    }
}

bool reach(Point p1, Point p2) {
    //function specially for Darth Sidious's 1st ability
    if (p1.x == 0 && p1.y == 0 && p2.x == 0 && p2.y == 0) {
        return false;
    }
    else {
        return distance_pp(p1, p2) <= 6;
    }
}

void DarthSidious_1(vector<vector<string>> &map_content, vector<character> &living, Point poles[]) {
    // so dumb
    if (living[search("DarthSidious", living)].get_poe() < 15) {
        cout << "your POE (points of energy) is not enough!" << endl;
        return;
    }
    else {
        int count = 0;
        for (int i = 0; i < living.size(); i++) {
            if (living[i].life && living[i].get_role() != "DarthSidious") {
                Point lord = living[search("DarthSidious", living)].get_coordinates();
                Point p1 = poles[0];
                Point p2 = poles[1];
                Point tar = living[i].get_coordinates();
                if (reach(lord, tar)) {
                    count++;
                    living[i].update_hp(-105);
                    cout << living[i].get_role() << " directly attacked, his HP -= 105 and is now: " << living[i].get_hp() << endl;
                }
                else if (reach(lord, p1) && reach(p1, tar)) {
                    count++;
                    living[i].update_hp(-105);
                    cout << living[i].get_role() << "is attacked, electricity conducted by pole at ( " << p1.x << ", " << p1.y << "), his HP -= 105 and is now : " << living[i].get_hp() << endl;
                }
                else if (reach(lord, p2) && reach(p2, tar)) {
                    count++;
                    living[i].update_hp(-105);
                    cout << living[i].get_role() << "is attacked, electricity conducted by pole at ( " << p2.x << ", " << p2.y << "), his HP -= 105 and is now : " << living[i].get_hp() << endl;
                }
                else if (reach(lord, p1) && reach(p1, p2) && reach(p2, tar)) {
                    count++;
                    living[i].update_hp(-105);
                    cout << living[i].get_role() << "is attacked, electricity conducted by poles at ( " << p1.x << ", " << p1.y << "), and ( " << p2.x << ", " << p2.y << "), his HP -= 105 and is now : " << living[i].get_hp() << endl;
                }
                else if (reach(lord, p2) && reach(p2, p1) && reach(p1, tar)) {
                    count++;
                    living[i].update_hp(-105);
                    cout << living[i].get_role() << "is attacked, electricity conducted by poles at ( " << p2.x << ", " << p2.y << "), and ( " << p1.x << ", " << p1.y << "), his HP -= 105 and is now : " << living[i].get_hp() << endl;
                }
            }
        }
        if (count == 0) {
            cout << "Oops, seems like you hit nobody! \n";
        }
        living[search("DarthSidious", living)].consume_poe(15);
        cout << "your current POE (points of energy) is: " << living[search("DarthSidious", living)].get_poe() << endl;
    }
}

void DarthSidious_2(Point poles[], vector<vector<string>> &map_content, vector<character> &living, int &which) {
    if (living[search("DarthSidious", living)].get_poe() < 15) {
        cout << "your POE (points of energy) is not enough! \n";
        return;
    }
    else {
        living[search("DarthSidious", living)].update_hp(50);
        Point to_place = living[search("DarthSidious", living)].get_coordinates();
        to_place.y += 1;
        if (to_place.y > 20) {
            cout << "you cannot place it outside map! Your HP and POE is unchanged.\n";
            return;
        }
        living[search("DarthSidious", living)].consume_poe(15);
        int index = which % 2;
        if (((index == 0 && (!(to_place.x == poles[1].x && to_place.y == poles[1].y) )) || (index == 1 && (!(to_place.x == poles[0].x && to_place.y == poles[0].y) ))) && map_content[20-to_place.y][to_place.x-1] == "") {
            poles[index] = to_place;
            cout << "electric pole placed successfully! \n";
            which++;
        }
        else {
            cout << "Failed to place the pola, because poles have to be placed at empty cells. However HP += 50 \n";
        }
        cout << "your current HP and POE: " << living[search("DarthSidious", living)].get_hp() << " and " << living[search("DarthSidious", living)].get_poe() << endl;
    }
}