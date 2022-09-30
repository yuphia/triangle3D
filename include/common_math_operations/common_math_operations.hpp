#pragma once

#include <cmath>
#include <iostream>

namespace geometry
{

class Point_t;
class Vector_t;
class Line_t;
class Plane_t;

enum class Degeneracy_t { NONE = 0, POINT, NULL_VECTOR, LINE, LINE_SEGMENT, INVALID = -1, POIZON}; 
                                                      //LINE not used

const double EPS = 10e-9;

inline double sqr (const double x);
inline bool equal_eps (const double x, const double y);


inline double sqr (const double x)
{
    return x * x;
}

inline bool equal_eps (const double x, const double y)
{
    return (fabs(x - y) < EPS);    
}

}