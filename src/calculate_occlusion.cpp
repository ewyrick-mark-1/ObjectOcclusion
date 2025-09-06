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
	//cout << angle << "\n";
	return angle;
}

void calculate_minmax(Box box, array<float, 2> &minmax) {
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

void calculate_wrap_minmax(Box box,
                           array<float, 2>& minmax_below,
                           array<float, 2>& minmax_above) {
    // Below = [min_high, 360]
    // Above = [0, max_low]

    float min_high = 360.0f; // smallest angle > 180
    float max_low  = 0.0f;   // largest angle ≤ 180

    //cout << "wrap was called on: ";
    //box.printCords();

    for (int j = 0; j < 4; j++) {
        float angle = calculateAngle(box.corners[j]);
        if (angle > 180.0f) {
            if (angle < min_high) min_high = angle;
        } else {
            if (angle > max_low) max_low = angle;
        }
    }

    // Build intervals
    minmax_below[0] = min_high;
    minmax_below[1] = 360.0f;

    minmax_above[0] = 0.0f;
    minmax_above[1] = max_low;
}

void merge(vector<array<float, 2>>& box_angles, int l, int m, int r){//basic merge function
    int left_size = m - l +1;
    int right_size = r - m;
    //temps
    vector<array<float, 2>> L(left_size);
    vector<array<float, 2>> R(right_size);
    
    //copy temps
    for(int i = 0; i < left_size; i++){
        L[i] = box_angles[l + i];
    }
    for(int i = 0; i < right_size; i++){
        R[i] = box_angles[m + 1 + i];
    }

    //do the actual merging
    int i = 0;
    int j = 0;
    int k = l;
    while(i < left_size && j < right_size){
        if(L[i][0] <= R[j][0]){
            box_angles[k++] = L[i++];
        } else {
            box_angles[k++] = R[j++];
        }

    }
    //take care of the rest
    while (i < left_size){
        box_angles[k++] = L[i++];
    }
    while (j < right_size){
        box_angles[k++] = R[j++];
    }

}

void mergesort(vector<array<float, 2>>& box_angles, int left, int right){
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergesort(box_angles, left, mid);       // Sort first half
        mergesort(box_angles, mid + 1, right); // Sort second half

        merge(box_angles, left, mid, right);   // Merge sorted halves
    }

}
void print_overlap(vector<array<float, 2>>& list){
    cout <<"overlap range: ";
    for(int i = 0; i < list.size(); i++){
        cout<<"["<<list[i][0]<<", "<<list[i][1]<<"], ";
    }
    cout <<"\n";
}
vector<array<float, 2>> calculate_occlusion( vector<Box>& boxes) {
    //get vector of min and max angles
    vector<array<float, 2>> minmax(boxes.size());
    
    for(int i = 0; i < boxes.size(); i++){
        calculate_minmax(boxes[i], minmax[i]);
        //wraparound, splits angles into two pairs. one in range [0, 180] and one in range [180, 360].
        if(minmax[i][1] - minmax[i][0] > 180){
            
            array<float, 2> minmax_above;
            array<float, 2> minmax_below;
            calculate_wrap_minmax(boxes[i], minmax_below, minmax_above );

            minmax.push_back(minmax_below);
            minmax[i] = minmax_above;
            
        }
    }
    
    
    mergesort(minmax, 0, minmax.size() - 1);
 
    vector<array<float, 2>> overlap;
    
        //overlap check
    float current_max = minmax[0][1];

    for (int i = 1; i < minmax.size(); i++) {
        float next_min = minmax[i][0];
        float next_max = minmax[i][1];

        if (next_min < current_max) {
        // intersection region
            overlap.push_back({next_min, min(current_max, next_max)});
        }

    // always extend current max
    current_max = max(current_max, next_max);
    }
    //merge
        for(int i = 0; i < overlap.size() - 1; i++){
            float current_min = overlap[i][0];
            float current_max = overlap[i][1];
            float next_min = overlap[i+1][0];
            float next_max = overlap[i+1][1];
            if (next_min <= current_max){
                //do merge
                overlap[i] = {current_min, next_max};
                overlap.erase(overlap.begin() + i + 1);
                i--;
            }
        }
    float total = 0.0;
    for(int i = 0; i < overlap.size(); i++){
        total += (overlap[i][1] - overlap[i][0]);
    }
    cout << "\n\n\n";
    print_overlap(overlap);
    cout << "total overlap: " << total << "\n";
    return overlap;
}    


