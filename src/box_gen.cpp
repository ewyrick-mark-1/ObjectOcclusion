#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <algorithm>


using namespace std;
float pi = 3.1415;


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

    Box(int distance, int length, int width, int orientation_angle, int angle, int id) {
        this->distance = distance;
        this->length = length;
        this->width = width;
        this->angle = angle;
        this->orientation_angle = orientation_angle;
        this->id = id;

        corner0[0] = distance * cos(orientation_angle * (pi / 180));
        corner0[1] = distance * sin(orientation_angle * (pi / 180));

        corner1[0] = (width * cos(angle * (pi / 180)) + corner0[0]);
        corner1[1] = (width * sin(angle * (pi / 180)) + corner0[1]);

        corner2[0] = (-length * sin(angle * (pi / 180)) + corner0[0]);
        corner2[1] = (length * cos(angle * (pi / 180)) + corner0[1]);

        corner3[0] = (width * cos(angle * (pi / 180)) + corner2[0]);
        corner3[1] = (width * sin(angle * (pi / 180)) + corner2[1]);

        //finds bounding coordinates

        float box_x[4] = { corner0[0], corner1[0], corner2[0], corner3[0] };
        float box_y[4] = { corner0[1], corner1[1], corner2[1], corner3[1] };

        bounding_x[0] = *min_element(begin(box_x), end(box_x));
        bounding_x[1] = *max_element(begin(box_x), end(box_x));

        bounding_y[0] = *min_element(begin(box_y), end(box_y));
        bounding_y[1] = *max_element(begin(box_y), end(box_y));


        for (int i = 0; i < 2; i++) {//puts all the corners in one array to make calculating the occlusion easier
            corners[0][i] = corner0[i];
            corners[1][i] = corner1[i];
            corners[2][i] = corner2[i];
            corners[3][i] = corner3[i];
        }



    }

    void printCords() {
        cout << "(" << corner0[0] << ", " << corner0[1] << ")" << ", ";
        cout << "(" << corner1[0] << ", " << corner1[1] << ")" << ", ";
        cout << "(" << corner2[0] << ", " << corner2[1] << ")" << ", ";
        cout << "(" << corner3[0] << ", " << corner3[1] << ")" << "\n";
    }
};


bool checkIntersect(Box boxA, Box boxB) {
    float x1a = boxA.bounding_x[0];//min box a x
    float x2a = boxA.bounding_x[1];//max box a x
    float y1a = boxA.bounding_y[0];//min box a y
    float y2a = boxA.bounding_y[1];//max box a y
    float x1b = boxB.bounding_x[0];//min box b x
    float x2b = boxB.bounding_x[1];//max box b x
    float y1b = boxB.bounding_y[0];//min box b y
    float y2b = boxB.bounding_y[1];//max box b y


    bool overlap = !(x2a <= x1b ||  // A is left of B
        x1a >= x2b ||  // A is right of B
        y2a <= y1b ||  // A is below B
        y1a >= y2b);   // A is above B

    return overlap;
}

//function that compares a proposed new box to the coordinates of the other boxes.
//It creates a bounding box around every generated box and maekes sure that the proposed box is not within those coordinates
bool checkValid(vector<Box> Boxes, Box box) {

    for (int i = 0; i < Boxes.size(); i++) {

        Box currentBox = Boxes[i];
        if (checkIntersect(currentBox, box)) {
            cout << "box gen failed.--------------------------------------------------------\n";
            return false;
        }
    }
    return true;
}





vector<Box> generate_boxes(int total_boxes, int min_radius, int max_radius, int min_box_bounds, int max_box_bounds) {
    vector<Box> Boxes;
    Boxes.reserve(total_boxes);
    float rand_distance, rand_length, rand_width, rand_angle, rand_orientation_angle; // code for generating random values is from gpt

    // Create a random number generator (Mersenne Twister).
    // 'static' ensures we only seed it once no matter how many times
    // generate_boxes() is called.
    static mt19937 rng(random_device{}());

    // Define distributions for each parameter.
    // radius: from 1 to max_radius
    uniform_int_distribution<int> dist_radius(min_radius, max_radius);
    // box length/width: from 1 to max_box_bounds
    uniform_int_distribution<int> dist_bounds(min_box_bounds, max_box_bounds); 
    // angles: from 0 to 359 degrees
    uniform_int_distribution<int> dist_angle(0, 359);



    for (int i = 0; i < total_boxes; i++) {

        rand_distance = dist_radius(rng);   // distance from origin
        rand_length = dist_bounds(rng);   // length of the box
        rand_width = dist_bounds(rng);   // width of the box
        rand_angle = dist_angle(rng);    // random orientation angle
        rand_orientation_angle = dist_angle(rng);    // some other reference angle
        Box new_box = Box(rand_distance, rand_length, rand_width, rand_orientation_angle, rand_angle, i);
        if (Boxes.empty() || checkValid(Boxes, new_box)) {
            //cout << rand_distance << ", " << rand_length << ", " << rand_width << ", " << rand_angle << "\n\n";
            new_box.id = i;
            Boxes.push_back(new_box);
            cout << "created Box " << i << "\n";
            Boxes[i].printCords();
        }
        else {
            i--;
        }
    }

    return Boxes;
}

