// character.h
#ifndef CHARACTER_H 
#define CHARACTER_H

#include <string>
#include <vector>

struct Point {int x, y;};

class character {
public:
    character(std::string role);

    void beginning_of_turn();

    void display_status();

    int poe_gen();

    void set_poe(int poe) {this->poe = poe;};
    
    void consume_poe(int comsumption) { poe -= comsumption; };

    int get_poe() {return poe;};

    std::string get_role() {return role;};

    void update_pos(int i, int j) {coordinates.x += i; coordinates.y += j; };

    void set_pos(int i, int j) {coordinates.x = i; coordinates.y = j; };

    Point get_coordinates() {return coordinates;};

    int get_hp() {return hp;};
    
    void update_hp(int hp_change) { 
        if (shield_buff) {
            std::cout << "The damage is absorbed by shield buff. \n";
            shield_buff = 0;
        }
        else if (role == "TuskenRaider" && hp_change < 0) {
            int a = rand() % 4;
            if (a == 0) {
                std::cout << "didn't change? Because TuskenRaider dodged this damage. Oops! \n";
            }
            else {
                hp += hp_change;
            }
        }
        else {
            hp += hp_change;
        }
    };

    void set_hp(int hp) {this->hp = hp;};

    void update_health_buff(int update=-1);

    void set_health_buff(int buff) {health_buff = buff;};

    int get_health_buff() {return health_buff;};

    void set_shield_buff(int buff) {shield_buff = buff;};

    int get_shield_buff() { return shield_buff; };

    std::string get_symbol() {return symbol;};

    double get_mass() {return mass;};

    bool life;
    int damage;
    int distance;
    bool penetrate;
    bool control;
    bool inward;
    int control_distance;

private:
    std::string role;
    Point coordinates;
    int hp;
    int max_poe;
    int poe;
    double mass;
    int health_buff;
    int shield_buff;
    std::string symbol;
};

using namespace std;

double min_distance(double x, double y, vector<vector<string>> map_content);
double distance_pl(Point x, Point a, Point b);
double distance_pp(Point x, Point y);
bool penetrate_se(Point start, Point end, vector<vector<string>> map_content, Point &intercept);
bool penetrate_sd(character controller, Point start, Point direction, int distance, vector<vector<string>> map_content, Point& intercept);



#endif