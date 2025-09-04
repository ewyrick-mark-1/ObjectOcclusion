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



using namespace sf;
using namespace std;

void draw_visuals(const vector<Box> boxes, const vector<array<float, 2>>& occluded, unsigned int radius, int max_dimention) {//rm max dimention if I dont get around to fixing window clipping
    float pi = 3.1415;

    ContextSettings settings;
    settings.antiAliasingLevel = 16;
    // create the window
    RenderWindow window(sf::VideoMode({ radius*2, radius*2}), "Object Occlusion");

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = window.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);
        
        CircleShape circle(radius, 2*pi*radius);
        window.draw(circle);

        CircleShape center(5);
        center.setPosition({ (float)radius, (float)radius });
        center.setFillColor(sf::Color(250, 0, 0));
        window.draw(center);

        CircleShape test(5);
        //center.setPosition({ (float)radius, (float)radius });
        test.setFillColor(sf::Color(250, 0, 0));
        window.draw(test);

        //draw angles

        for(int i = 0; i < occluded.size(); i++){
            ConvexShape shape;
            shape.setPointCount(3);
            float x1 = (2*radius)*cos(occluded[i][0] * (pi/180));
            float y1 = (2*radius)*sin(occluded[i][0] * (pi/180));
            float x2 = (2*radius)*cos(occluded[i][1] * (pi/180));
            float y2 = (2*radius)*sin(occluded[i][1] * (pi/180));
            shape.setPoint(0, {(float)radius, (float)radius});
            shape.setPoint(1, {x1 + radius, -y1 + radius});
            shape.setPoint(2, {x2 + radius, -y2 + radius});

            shape.setFillColor(sf::Color(250, 0, 0));

            window.draw(shape);
        }

        //draw boxes
        for (int i = 0; i < boxes.size(); i++) {
            ConvexShape shape;
            shape.setPointCount(4);
            shape.setPoint(0, { boxes[i].corner0[0] + radius, -boxes[i].corner0[1] + radius });
            shape.setPoint(1, { boxes[i].corner1[0] + radius, -boxes[i].corner1[1] + radius });
            shape.setPoint(2, { boxes[i].corner3[0] + radius, -boxes[i].corner3[1] + radius });
            shape.setPoint(3, { boxes[i].corner2[0] + radius, -boxes[i].corner2[1] + radius });//had to mix them up a little because of how I calculated the verts
            shape.setFillColor(sf::Color(100, 250, 50));

            window.draw(shape);
        }
        
        
        // end the current frame
        window.display();
    }
}