#include "vector/vector.hpp"

namespace geometry
{
    Vector_t::Vector_t (const double x_, const double y_, const double z_) : x(x_), y(y_), z(z_){}
    Vector_t::Vector_t (const Point_t& point) : x(point.x), y(point.y), z(point.z){}

    inline bool Vector_t::operator== (const Vector_t& rhs) const
    {
        return (equal_eps(x, rhs.x) && equal_eps(y, rhs.y) && equal_eps(z, rhs.z));
    }

    inline Vector_t Vector_t::operator+ (const Vector_t& rhs) const 
    {
        Vector_t sum (x + rhs.x, y + rhs.y, z + rhs.z);
        return sum;
    }

    inline Vector_t Vector_t::operator-() const
    {
        Vector_t negation (-x, -y, -z);
        return negation;
    }

    inline Vector_t Vector_t::operator- (const Vector_t& rhs) const 
    {
        return Vector_t::operator+ (-rhs);
    }

    inline void Vector_t::operator= (const Vector_t& rhs) 
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        length = rhs.length;
    }

    bool Vector_t::is_collinear_to (const Vector_t& vec) const
    {
        return (equal_eps(vec.x/x, vec.y/y) && equal_eps(vec.y/y, vec.z/z));
    }
    
    inline double Vector_t::operator*  (const Vector_t& rhs)
    {
        return (x * rhs.x + y * rhs.y + z * rhs.z);
    }

    inline Vector_t Vector_t::operator%  (const Vector_t& rhs)
    {
        return (Vector_t {y * rhs.z - z * rhs.y, 
                        -(x * rhs.z - z * rhs.x), 
                          x * rhs.y - y * rhs.x});
    }

} //geometry