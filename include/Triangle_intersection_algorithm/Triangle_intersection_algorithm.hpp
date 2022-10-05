#pragma once

#include "point/point.hpp"
#include "vector_geom/vector_geom.hpp"
#include "line/line.hpp"
#include "line_segment/line_segment.hpp"
#include "plane/plane.hpp"
#include "AABB/AABB.hpp" //triangle.hpp is already here


namespace geometry
{ 

// main algorithm functions ======================================================================================================================
    
    double          signed_distance                                 (const Point_t& P, const Plane_t& plane);                                   //done
    Line_t          construct_intersection_line                     (const Plane_t& first, const Plane_t& second);                              //done
    double          point_on_line_projection_coeff                  (const Point_t& point, const Line_t& line);                                 //
    void            compute_triangle_projection_on_line             (const Triangle_t& triangle, const Line_t& line, double& min, double& max); //  
    void            compute_triangle_projection_interval            (const Triangle_t& triangle, const Plane_t& other_triangle_plane, const Line_t& line, double& min, double& max);
    bool            do_triangles_intersect                          (const Triangle_t& T0, const Triangle_t& T1);                               //

//================================================================================================================================================


// 2D case functions =============================================================================================================================
    
    Line_t          construct_perpendicular_line_in_plane           (const Plane_t& plane, const Line_t& line);
    bool            do_triangles_in_the_same_plane_intersect        (const Plane_t& plane, const Triangle_t& first, const Triangle_t& second);

//================================================================================================================================================


// degeneration case functions ===================================================================================================================
    
    bool            select_and_run_algo_for_degenerated_triangles   (const Triangle_t& T0, const Triangle_t& T1);                           
    bool            do_line_segment_and_triangle_intersect          (const Triangle_t& degenerated_to_segment, const Triangle_t& triangle); 
    bool            do_point_and_triangle_intersect                 (const Point_t& point, const Triangle_t& triangle);                       
    bool            do_line_segments_intersect                      (const Line_segment_t& first, const Line_segment_t& second);            
    Line_segment_t  convert_to_line_segment                         (const Triangle_t& triangle);                                           

//================================================================================================================================================

} //geometry