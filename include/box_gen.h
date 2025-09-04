// boxes.h, made the header with chatgpt.
#pragma once

#include <vector>


//test
using std::vector;

struct Box {
public:
    int distance;
    int length;
    int width;
    int angle;
    int orientation_angle;
    int id;

    float corner0[2];
    float corner1[2];
    float corner2[2];
    float corner3[2];
    float bounding_y[2];
    float bounding_x[2];

    float corners[4][2];

    // Constructor
    Box(int distance, int length, int width, int orientation_angle, int angle, int id);

    // Print corners for debugging
    void printCords();
};

// Check if two boxes intersect
bool checkIntersect(Box boxA, Box boxB);

// Check if a proposed box is valid (does not intersect existing boxes)
bool checkValid(const vector<Box>& Boxes, Box box);

// Generate multiple boxes with random parameters
vector<Box> generate_boxes(int total_boxes, int min_radius, int max_radius, int min_box_bounds, int max_box_bounds);
