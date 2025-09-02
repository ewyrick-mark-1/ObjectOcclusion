#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <algorithm>

#include "box_gen.h"

using namespace std;


float calculateAngle(float corner[]) {
	//cout << "corner=(" << corner[0] << "," << corner[1] << ") -> ";
	float angle = atan2(corner[1], corner[0]) * (180.0 / 3.1415);
	if (angle < 0) angle += 360.0f;
	cout << angle << "\n";
	return angle;
}

void calculate_box_occlusion(Box box, array<float, 2> &minmax) {
	minmax[0] = 360;// {min, max}
	minmax[1] = 0;
	for (int j = 0; j < 4; j++) { //o1
		float angle = calculateAngle(box.corners[j]);
		if (angle < minmax[0]) {
			minmax[0] = angle;
		 }
		if (angle > minmax[1]) {
			minmax[1] = angle;
		}

	}
	

}

float calculate_occlusion(const std::vector<Box> boxes) {
    vector<array<float,2>> non_visible_range;

    for (int i = 0; i < boxes.size(); i++) {
        std::array<float,2> occluded;
        calculate_box_occlusion(boxes[i], occluded);

        if (non_visible_range.empty()) {
            non_visible_range.push_back(occluded);
            continue;
        }

        bool merged = false;
        for (int j = 0; j < non_visible_range.size(); j++) {
            // overlap
            if (occluded[0] <= non_visible_range[j][1] && occluded[1] >= non_visible_range[j][0]) {
                non_visible_range[j][0] = std::min(non_visible_range[j][0], occluded[0]);
                non_visible_range[j][1] = std::max(non_visible_range[j][1], occluded[1]);
                merged = true;
                break;  // merged, stop inner loop
            }
            // comes before current range
            else if (occluded[1] < non_visible_range[j][0]) {
                non_visible_range.insert(non_visible_range.begin() + j, occluded);
                merged = true;
                break;
            }
        }

        if (!merged) {
            non_visible_range.push_back(occluded);
        }
    }

    // compute total occlusion
    float total_occlusion = 0;
    for (int i = 0; i < non_visible_range.size(); i++) {
        total_occlusion += non_visible_range[i][1] - non_visible_range[i][0];
    }
    cout << "total occlusion: " <<total_occlusion << "\n";
    return total_occlusion;
}


