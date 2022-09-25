#include "vector/vector.hpp"
#include "point/point.hpp"


namespace geometry
{

class Plane_t {

private:
    Vector_t normal = {};
    double d = std::numeric_limits<double>::quiet_NaN();

public:
    Plane_t (const Point_t& pt1, const Vector_t& vec1, const Point_t& vec2);
    Plane_t (const Point_t& pt1, const Line_t& line);
    Plane_t (const Point_t& pt1, const Point_t& pt2, const Point_t& pt3);
    Plane_t (const Point_t& pt, const Vector_t& n);
    Plane_t (const double A, const double B, const double C, const double D);

}

}
