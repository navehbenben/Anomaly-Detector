
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
	Point center;
	float radius;
	Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

Circle CenterPoint (Point a, Point b, Point c);

bool isInCircle(Circle circle, Point p);
// you can add here additional methods

bool Cor_isInCircle(Circle circle, Point p);

#endif /* MINCIRCLE_H_ */
