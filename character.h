// character.h
#ifndef CHARACTER_H 
#define CHARACTER_H

#include <string>

struct Point {int x, y;};

class character {
public:
    character(std::string role);

    void beginning_of_turn();

    void display_status();

    int poe_gen();

    void set_poe(int poe) {this->poe = poe;};

    int get_poe() {return poe;};

    std::string get_role() {return role;};

    void update_pos(int i, int j) {coordinates.x += i; coordinates.y += j; };

    void set_pos(int i, int j) {coordinates.x = i; coordinates.y = j; };

    Point get_coordinates() {return coordinates;};

    int get_hp() {return hp;};
    
    void update_hp(int hp_change) {hp += hp_change;};

    void set_hp(int hp) {this->hp = hp;};

    void update_health_buff(int update=-1);

    void set_health_buff(int buff) {health_buff = buff;};

    int get_health_buff() {return health_buff;};

    std::string get_symbol() {return symbol;};

    double get_mass() {return mass;};

private:
    std::string role;
    Point coordinates;
    int hp;
    int max_poe;
    int poe;
    double mass;
    int health_buff;
    std::string symbol;
};

double min_distance(double x, double y, vector<vector<string>> map_content);
double distance_pl(Point x, Point a, Point b);
double distance_pp(Point x, Point y);
bool penetrate_se(Point start, Point end, vector<vector<string>> map_content, Point &intercept);



#endif