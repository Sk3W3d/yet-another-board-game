// character.cpp
#include <string>
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "character.h"

character::character(std::string role){
    coordinates = {0, 0};
    this->role = role;
    poe = 0;
    if (role == "Luke Skywalker"){ 
        hp = 480;
        max_poe = 40;
        mass = 0.8;
        symbol = "\uA19C";
    } else if (role == "Han Solo")
    {
        /* code */
    }
    
}

int character::poe_gen(){
    srand(time(0));
    int roll = rand()%6;
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
    std::cout << "Buff status: " << health_buff << std::endl;
}