#include "point/point.hpp"

namespace geometry
{
class Vector
{
private:
    Point coords;

    double len = std::numeric_limits<double>::quiet_NaN();
    bool is_synched = false;

public:
    Vector (double x_, double y_, double z_);

    void synchronize();
    double get_this_length();
    inline double dot (const Vector& v) const;
   
    inline Vector operator+ (const Vector& rhs) const;
    inline bool operator== (const Vector& rhs) const;
    
    bool is_synched_ask() const;
};
}