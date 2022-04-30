// character.h
#include <string>

struct Point {int x, y;};

class character {
public:
    character(std::string role);
    int poe_gen();
    std::string get_role() {return role;};

    void update_pos(int i, int j) {coordinates.x += i; coordinates.y += j; };

    Point get_coordinates() {return coordinates;};

    int get_hp() {return hp;};
    
    void update_hp(int hp_change);

    void update_buff();


private:
    std::string role;
    Point coordinates;
    int hp;
    int max_poe;
    int poe;
    int mass;
    int health_buff;
    char symbol;
};