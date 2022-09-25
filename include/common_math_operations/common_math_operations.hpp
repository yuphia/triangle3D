#include <cmath>

namespace geometry
{
const double EPS = 10e-9;

double sqr (const double x);
bool equal_eps (const double x, const double y);

double sqr (const double x)
{
    return x*x;
}

bool equal_eps (const double x, const double y)
{
    return (x - y) < EPS;    
}
}