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
    }
    //sort by min angle
    mergesort(minmax, 0, boxes.size() - 1);
    print_overlap(minmax);
    //move through linerally and parse into visible / non visible ranges
    vector<array<float, 2>> overlap;
    float current_min = minmax[0][0];
    float current_max = minmax[0][1];
    for(int i = 1; i < minmax.size(); i++){
        if(minmax[i][0] < current_max){ //overlap
            
            if(minmax[i][1] > current_max){ //partial overlap
                overlap.push_back({minmax[i][0], current_max}); // logs overlap
                current_min = current_max;
                current_max = minmax[i][1];
            } else { //full overlap
                overlap.push_back({minmax[i][0], minmax[i][1]}); // log overlap
                current_min = minmax[i][1];//adjust lower bound to prevent double count
            }

        } else { // no overlap, adjust bounds
            current_min = minmax[i][0];
            current_max = minmax[i][1];
        }
    }
    print_overlap(overlap);
    return overlap;
}    


