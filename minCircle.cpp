#include "minCircle.h"
#include <math.h>
#include <vector>
#include <set>


Circle one_point(Point center){
    return Circle(center, (float)0);
}

double distance(Point a, Point b){

    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
    //return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

Point middle(Point a, Point b){
    return Point((a.x+b.x)/2,(a.y+b.y)/2);
}

Circle two_points(Point a, Point b){
    float diameter = distance(a,b);
    Point center = middle(a,b);
    return Circle(center, diameter/2);
}



Circle CenterPoint (Point a, Point b, Point c){

    double bx=b.x-a.x;
    double by=b.y-a.y;
    double cx=c.x-a.x;
    double cy=c.y-a.y;

  double X= bx * bx + by * by;
  double Y=cx * cx + cy * cy;
  double Z= bx * cy - by * cx;
  Point d= Point((cy *X - by * Y) / (2 * Z),
            (bx * Y - cx * X) / (2 * Z));
            d.x+=a.x;
            d.y+=a.y;
    double ad = distance(a,d);
    double bd = distance(b,d);
    double cd = distance(c,d);
    if (ad>=bd&&bd>=cd)
    {
        return Circle(d, ad);
    }
    if (bd >= cd)
    {
     return Circle(d, bd);
    }
    return Circle(d, cd);

}

bool isInCircle(Circle circle, Point p){
    return distance(p,circle.center)<=circle.radius;
}

bool Cor_isInCircle(Circle circle, Point p){
    return distance(p,circle.center)<=(1.1*circle.radius);
}

// Circle bounded_circle(Point a, Point b, Point c){
//     Point ab = middle(a,b);
//     Point bc = middle(b,c);
//     Point ac = middle(a,c);
    
// }

// Circle threePoints(Point a, Point b ,Point c){
//     Circle A = two_points(a,b);
//     Circle B = two_points(b,c);
//     Circle C = two_points(a,c);
//     Circle bound = CenterPoint(a,b,c);

// }


Circle WELZL(Point** P,int P_size, vector<Point> R, int R_size){
    Circle res = Circle(Point(0,0),0);
    if (P_size ==0||R_size==3)
    {
        if(R_size<=3){
            if(R_size==3){
            res = CenterPoint(R[0],R[1],R[2]);
            return res;
            }
            if(R_size==2){
            res = two_points(R[0],R[1]);
            return res;
            }
            if(R_size==1){
            res = Circle(R[0],0);
            return res;
            }
        }
        if (P_size ==0){
            return res;
        }
    }
    else {
        Point p = *(P[P_size-1]);
        //P.pop_back();
        Circle first = WELZL(P,P_size-1,R, R_size);
        if (isInCircle(first,p)){
            res = first;
        }
        else {
            R.push_back(p);
            res = WELZL(P,P_size-1,R, R_size + 1);
        }
    }
    return res;
}



Circle findMinCircle(Point** points,size_t size){
    // vector<Point> pointVect = vector<Point>();
    // for (size_t i = 0; i < size; i++)
    // {
    //     pointVect.push_back(*points[i]);
    // }
    
    vector<Point> empty = vector<Point>();
    return WELZL(points, size, empty, 0);
}
