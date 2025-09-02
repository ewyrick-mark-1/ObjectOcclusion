#pragma once
// visuals.h
#pragma once   // prevents multiple inclusion
#include <iostream>
#include <SFML/Graphics.hpp>


#include "box_gen.h"

void draw_visuals(vector<Box>, unsigned int radius, int max_dimention);  // function declaration only
void createWindow(float radius);
void drawRectangle(sf::RenderWindow& window, float corner0[2], float corner1[2], float corner2[2], float corner3[2]);

