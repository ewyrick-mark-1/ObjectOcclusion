#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <algorithm>

#include "visuals.h"
#include "box_gen.h"
#include "calculate_occlusion.h"

using namespace std;

int NUM_BOXES = 1000;
int MIN_RADIUS = 50;
int MAX_RADIUS = 400; // will also be the radius of the display in pixels
int MAX_DIMENTIONS = 40;

int main() { 
    srand(time(nullptr));
    
    vector<Box> Boxes = generate_boxes(NUM_BOXES, MIN_RADIUS, MAX_RADIUS - MAX_DIMENTIONS, MAX_DIMENTIONS);
    calculate_occlusion(Boxes);
    draw_visuals(Boxes, MAX_RADIUS, MAX_DIMENTIONS);
   
    return 0;
}