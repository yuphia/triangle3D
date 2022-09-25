#include "point/point.hpp"

namespace geometry
{
class Vector_t
{
private:
    double length = std::numeric_limits<double>::quiet_NaN();

public:
    double x, y, z = std::numeric_limits<double>::quiet_NaN();

    Vector_t (const double x_, const double y_, const double z_);
    Vector_t (const Point_t& point);
    
    inline bool     operator== (const Vector_t& rhs) const;
    inline Vector_t operator+  (const Vector_t& rhs) const;
    inline Vector_t operator-  (const Vector_t& rhs) const;
    inline Vector_t operator-  () const;
    inline void     operator=  (const Vector_t& rhs);

    bool is_collinear_to (const Vector_t& vec) const;
};
}