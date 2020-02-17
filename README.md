# Tilemap-Collision-Detection-Test

NOTE: You will have to download the SFML libary yourself and include it in your project. You can download SFML here: https://www.sfml-dev.org/download/sfml/2.4.2/ . I used the Visual C++14 (2015) version.

Using a quadtree data structure, and the SFML library for visualization, I have put together an AABB based collision detector. 

Further optimizations are possible, i.e. switching to a K-D tree would likely be faster than using a quadtree. As of now, the project only detects collision for tiles on the screen, and not for tiles outside of it. 
