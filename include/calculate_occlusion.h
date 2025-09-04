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
#include "box_gen.h"


using std::vector;
using namespace std;

float calculateAngle(float corner[2]);

// Calculate the minimum and maximum angles for a box
void calculate_minmax(Box box, std::array<float, 2> &minmax);

// Merge sort for box angle ranges
void merge(vector<array<float, 2>>& box_angles, int l, int m, int r);
void mergesort(vector<array<float, 2>>& box_angles, int left, int right);

void print_overlap(vector<array<float, 2>>& list);

// Calculate occlusion from a vector of boxes
vector<array<float, 2>> calculate_occlusion(vector<Box>& boxes);

