// boxes.h, made the header with chatgpt.
#pragma once

#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include "box_gen.h";


using std::vector;
using namespace std;

float calculateAngle(float corner[]);

void calculate_box_occlusion(Box box, array<float, 2>& minmax);

float calculate_occlusion(vector<Box> boxes);

