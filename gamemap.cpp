// gamemap.cpp
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <random>
#include "gamemap.h"

#define WALL "\u2588\u2588"

void gamemap::init_map(){
    // map_content = std::vector<std::vector<std::string>>(20, std::vector<std::string>(40, ""));
    map_content = {
        {WALL, WALL, WALL, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", // 20 per line
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, // 40 per 1-d vector
        {WALL, WALL, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, 
        {WALL, "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", "", WALL, "", "", WALL, "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", "", WALL, "", "", WALL, "", "", "", "", "", "", "", "", "", "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", "", WALL, "", "", WALL, WALL, WALL, WALL, WALL, WALL, "", "", "", "", "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", "", WALL, "", "", "", "", "", "", "", "", WALL, "", "", "", "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", "", WALL, "", "", "", "", "", "", "", "", "", WALL, "", "", "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        "", WALL, "", "", "", "", "", WALL, WALL, "", "", "", "", WALL, "", "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        WALL, "", "", "", "", "", WALL, "", "", WALL, "", "", "", "", WALL, "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        WALL, "", "", "", "", WALL, "", "", "", "", WALL, "", "", "", WALL, "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        WALL, "", "", "", "", WALL, "", "", "", "", WALL, "", "", "", WALL, "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        WALL, "", "", "", "", WALL, "", "", "", "", WALL, "", "", "", WALL, "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
        WALL, "", "", "", "", "", "", "", "", "", WALL, "", "", "", WALL, "", "", "", "", ""}, 
        {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", WALL, WALL, 
        WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, "", "", ""}, 
        {"", "", "", WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, 
        WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}, 
        {"", "", WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, 
        WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}, 
        {"", WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, 
        WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}, 
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, 
        WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}, 
    };
    // for (int i = 0; i < 20; i++){
    //     for (int j = 0; j < 40; j++){
    //         if (map_content[i][j] == "") map_content[i][j] = "  ";
    //     }
    // }
}


void gamemap::output_map(){
    for (int i = 0; i < 20; i++){
        std::cout << std::setw(2) << 20-i;
        for (int j = 0; j < 40; j++){
            std::cout << std::setw(2) << map_content[i][j];
        }
        std::cout << std::endl;
    }
    for (int j = 0; j < 40; j++){
            std::cout << std::setw(2) << j;
        }
    std::cout << "\n";
}

void gamemap::element_gen(int round){
    if (round % 5 == 0){
        srand(time(0));
        // std::string health_buff = "\u002B ";
        int x = rand() / 20 % 20, y = rand()%20;
        while (map_content[x][y] != ""){
            x = rand() / 20 % 20, y = rand()%20;
        }
        update_map(x, y, "\u002B ");
        while (map_content[x][y] != ""){
            x = rand() / 20 % 20, y = rand()%20;
        }
        update_map(x, y, "\u25BF ");
    }
}