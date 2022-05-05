// character.cpp
#include <string>
#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <cmath>
#include "character.h"

#define WALL "\u2588\u2588"

using namespace std;

character::character(std::string role){
    coordinates = {0, 0};
    this->role = role;
    poe = 0;
    health_buff = 0;
    if (role == "LukeSkywalker"){ 
        hp = 480;
        max_poe = 40;
        mass = 0.8;
        symbol = "\uA19C";
        coordinates = {4, 5};
    } else if (role == "HanSolo")
    {
        hp = 480;
        max_poe = 55;
        mass = 1;
        symbol = "\uA167";
        coordinates = {4, 10};
    } else if (role == "Obi-wanKenobi")
    {
        hp = 580;
        max_poe = 60;
        mass = 1.2;
        symbol = "\uA010";
        coordinates = {4, 15};
    } else if (role == "R2D2")
    {
        hp = 580;
        max_poe = 60;
        mass = 1.2;
        symbol = "\uA010";
        coordinates = {8, 5};
    } else if (role == "Chewbacca")
    {
        hp = 800;
        max_poe = 100;
        mass = 2;
        symbol = "\uA12C";
        coordinates = {8, 10};
    } else if (role == "DarthVader")
    {
        hp = 480;
        max_poe = 50;
        mass = 1.1;
        symbol = "\uA111";
        coordinates = {8, 15};
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
        coordinates = {12, 8};
    } else if (role == "DarthMaul")
    {
        hp = 340;
        max_poe = 40;
        mass = 1;
        symbol = "\uA389";
        coordinates = {38, 10};
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
    std::cout << "Buff status: " << health_buff << std::endl;
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
            intersection[index][0] = start.x + ((end.x - start.x) / (end.y - start.y)) * (j + dy - start.y) , intersection[index][1] = j + dy;
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
