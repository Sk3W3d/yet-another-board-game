#include <iostream>
#include <string>
#include "gamemap.h"

using namespace std;

int main(){
    gamemap map;
    map.init_map();
    map.output_map();
    return 0;
}