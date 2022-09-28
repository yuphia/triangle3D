#pragma once

#include "point/point.hpp"
#include "vector/vector.hpp"
#include "line/line.hpp"
#include "line_segment/line_segment.hpp"
#include "plane/plane.hpp"
#include "triangle/triangle.hpp"


namespace geometry
{

// main algorithm functions ======================================================================================================================
    
    double          signed_distance                                 (const Point_t& P, const Plane_t& plane);
    Line_t          construct_intersection_line                     (const Plane_t& first, const Plane_t& second);
    double          point_on_line_projection_coeff                  (const Point_t& point, const Line_t& line);
    void            compute_triangle_on_line_projection_interval    (const Triangle_t& triangle, const Line_t& line, double* min, double* max);
    bool            is_intersection                                 (const Triangle_t& T0, const Triangle_t& T1);

//================================================================================================================================================


// 2D case functions =============================================================================================================================
    
    Line_t          construct_perpendicular_line_in_plane           (const Plane_t& plane, const Line_t& line);
    bool            is_intersection_in_plane                        (const Plane_t& plane, const Triangle_t& first, const Triangle_t& second);

//================================================================================================================================================


// degeneration case functions ===================================================================================================================
    
    bool            is_intersection_degeneration_case               (const Triangle_t& T0, const Triangle_t& T1);
    bool            is_intersection_line_segment_triangle           (const Line_segment_t& segment, const Triangle_t& triangle);
    bool            is_point_inside_triangle                        (const Point_t& point, const Triangle_t& triangle);
    bool            is_intersection_line_segments                   (const Line_segment_t& first, const Line_segment_t& second);
    Line_segment_t  convert_to_line_segment                         (const Triangle_t& triangle);

//================================================================================================================================================

} //geometry