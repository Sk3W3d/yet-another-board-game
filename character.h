// character.h
#include <string>

struct Point {int x, y;};

class character {
public:
    character(std::string role);

    void beginning_of_turn();

    void display_status();

    int poe_gen();

    std::string get_role() {return role;};

    void update_pos(int i, int j) {coordinates.x += i; coordinates.y += j; };

    Point get_coordinates() {return coordinates;};

    int get_hp() {return hp;};
    
    void update_hp(int hp_change);

    void update_health_buff(int update=-1);

    std::string get_symbol() {return symbol;};

private:
    std::string role;
    Point coordinates;
    int hp;
    int max_poe;
    int poe;
    int mass;
    int health_buff;
    std::string symbol;
};