README - Box Occlusion
==========================================

DESCRIPTION:
This program generates random rectangles around an origin point and calculates
the total occlusion angle where rectangles overlap from the origin's perspective.
It displays the results both numerically and visually.

FILES INCLUDED:
- main.cpp
- box_gen.cpp / box_gen.h
- calculate_occlusion.cpp / calculate_occlusion.h  
- visuals.cpp / visuals.h
- CmakeLists.txt

REQUIREMENTS:
- Cmake extension on VS code
- C++ compiler (g++ recommended)
- SFML Graphics Library installed

COMPILATION:
- Make a build directory
- Run cmake in that direcotry (cmake .)
- Run make in that directory (make)

USAGE:
1. Run the compiled program: ./occlusion from the build directory
2. Enter the number of rectangles when prompted
3. The program will:
   - Generate random rectangles
   - Calculate occlusion angles
   - Display results in terminal
   - Open a visual window showing the rectangles and occluded regions

VISUAL DISPLAY:
- Green rectangles: Generated boxes
- Red triangular sectors: Occluded angle ranges  
- Red dot: Origin point
- White circle: Box gen boundary

Press the window's close button to exit the visualization.
