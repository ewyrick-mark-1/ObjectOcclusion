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

int NUM_BOXES = 10;
int MIN_RADIUS = 50;
int MAX_RADIUS = 400; // will also be the radius of the display in pixels
int MAX_DIMENTIONS = 80;

int main() { 
    srand(time(nullptr));
    cin >> NUM_BOXES;
    vector<Box> Boxes = generate_boxes(NUM_BOXES, MIN_RADIUS, MAX_RADIUS - MAX_DIMENTIONS, MAX_DIMENTIONS);
    vector<array<float, 2>> occluded = calculate_occlusion(Boxes);
    draw_visuals(Boxes, occluded, MAX_RADIUS, MAX_DIMENTIONS);
   
    return 0;
}