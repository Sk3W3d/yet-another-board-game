// gamemap.h
#include <string>
#include <vector>

class gamemap {
public:

    void init_map();
    void output_map();
    void element_gen(int);
    std::vector<std::vector<std::string>> get_map_content();
    void update_map(int i, int j, std::string str) {map_content[i][j] = str;};

private:
    // Every game character occupies 2 places: 
    // ꆜ
    // ██
    // tt
    // Therefore, each block in the game is designed to occupy two places. 
    // The data type of vector<vector<string>> is used to store the contents of the map
    // The map size will be a 40*20 2D array of string
    std::vector<std::vector<std::string>> map_content;

};