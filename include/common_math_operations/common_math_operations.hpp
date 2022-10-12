#pragma once

#include <cmath>
#include <iostream>

namespace geometry
{

struct Point_t;
struct Vector_t;
struct Line_t;
struct Plane_t;

enum class Degeneracy_t { NONE = 0, POINT, NULL_VECTOR, LINE_SEGMENT, INVALID = -1, POIZON}; 
                                                      //LINE not used

const double EPS = 10e-9;


inline double sqr (const double x);
inline bool equal_eps (const double x, const double y);
inline int sign (const double x);


inline double sqr (const double x)
{
    return x * x;
}

inline bool equal_eps (const double x, const double y)
{
    return (fabs(x - y) < EPS);    
}

inline int sign (const double x)
{
    return (x > 0) - (x < 0);   
}

}