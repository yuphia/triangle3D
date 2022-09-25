#include <limits>
#include <cmath>
#include <common_math_operations/common_math_operations.hpp>

namespace geometry
{
class Point
{
public:
    double x = std::numeric_limits<double>::quiet_NaN();
    double y = std::numeric_limits<double>::quiet_NaN();
    double z = std::numeric_limits<double>::quiet_NaN();


};
}