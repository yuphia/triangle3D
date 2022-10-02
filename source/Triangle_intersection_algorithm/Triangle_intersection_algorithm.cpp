#include <cmath> 
#include "Triangle_intersection_algorithm/Triangle_intersection_algorithm.hpp"

    
namespace geometry
{

// main algorithm functions ====================================================================================================================== 
double signed_distance (const Point_t& P, const Plane_t& plane) {
    return (plane.normal * Vector_t{P} - plane.d);
}

//constructs inersection line of two planes (planes must not be degenerated or parallel)
// L(t) = (first_coeff * n1 + second_coeff * n2) + t * cross (n1, n2); <- formula which used in algorithm
Line_t construct_intersection_line (const Plane_t& first, const Plane_t& second) {
    
    double s1 = first.d;
    double s2 = second.d;
    double n1_dot_n2 =  first.normal * second.normal;

    double first_coeff  = (s2*n1_dot_n2 - s1) / (n1_dot_n2*n1_dot_n2 - 1.0);
    double second_coeff = (s1*n1_dot_n2 - s2) / (n1_dot_n2*n1_dot_n2 - 1.0);
    
    //std::cout << (first.normal*first_coeff + second.normal*second_coeff).x << ' ' << (first.normal*first_coeff + second.normal*second_coeff).y << ' ' << (first.normal*first_coeff + second.normal*second_coeff).z << std::endl;
    //std::cout << (first.normal*first_coeff + second.normal*second_coeff) * first.normal << ' ' << (first.normal*first_coeff + second.normal*second_coeff) * second.normal << std::endl;
    return Line_t{first.normal % second.normal, first.normal*first_coeff + second.normal*second_coeff};
}

double point_on_line_projection_coeff (const Point_t& point, const Line_t& line) {
    return ( (line.direction_vec * (Vector_t{point} - line.point_on_line)) / line.direction_vec.squared_length());
}

// can be templated on polygon, if triangle_t -> part of polygon_t
void compute_triangle_projection_on_line_segment (const Triangle_t& triangle, const Line_t& line, double& min, double& max) {
    
    min = max = point_on_line_projection_coeff (triangle.points[0], line);
    double term = min;
    
    for (size_t i = 1; i < triangle.nVertices; i++) {
        term = point_on_line_projection_coeff (triangle.points[i], line);
        if ( term < (min - EPS) )
            min = term;
        else if ( term > (max + EPS) )
            max = term;
    }

    return;
}

bool do_triangles_intersect (const Triangle_t& T0, const Triangle_t& T1) {
    
    if (T0.degeneracy != Degeneracy_t::NONE || T1.degeneracy != Degeneracy_t::NONE)
        return select_and_run_algo_for_degenerated_triangles (T0, T1);

    Plane_t T0_plane {T0.points[0], T0.points[1], T0.points[2]};
    //std::cout << signed_distance(T1.points[0], T0_plane) << ' ' << signed_distance(T1.points[1], T0_plane) << ' ' << signed_distance(T1.points[2], T0_plane) << std::endl;

    if ( ( signed_distance(T1.points[0], T0_plane) > 0 
           && 
           signed_distance(T1.points[1], T0_plane) > 0 
           && 
           signed_distance(T1.points[2], T0_plane) > 0   
         )   
         ||
         ( signed_distance(T1.points[0], T0_plane) < 0 
           && 
           signed_distance(T1.points[1], T0_plane) < 0 
           && 
           signed_distance(T1.points[2], T0_plane) < 0   
         ) 
        ) {
        //std::cout << "AAAAAAAAAAAA" << std::endl;
        return false;
        }

    Plane_t T1_plane {T1.points[0], T1.points[1], T1.points[2]};

    if (T0_plane | T1_plane) {
        if (T0_plane == T1_plane)
            return do_triangles_in_the_same_plane_intersect (T0_plane, T0, T1);
        else 
            return false;
    }

    if ( ( signed_distance(T0.points[0], T1_plane) > 0 
           && 
           signed_distance(T0.points[1], T1_plane) > 0 
           && 
           signed_distance(T0.points[2], T1_plane) > 0
         ) 
         ||
         ( signed_distance(T0.points[0], T1_plane) < 0 
           && 
           signed_distance(T0.points[1], T1_plane) < 0 
           && 
           signed_distance(T0.points[2], T1_plane) < 0
         ) 
       )
        return false;

    Line_t intersection_line = construct_intersection_line (T0_plane, T1_plane);

    double T0_min, T0_max, T1_min, T1_max = std::numeric_limits<double>::quiet_NaN();
    
    compute_triangle_projection_on_line_segment (T0, intersection_line, T0_min, T0_max);
    compute_triangle_projection_on_line_segment (T1, intersection_line, T1_min, T1_max);

    if ( T0_max < (T1_min - EPS) || T1_max < (T0_min - EPS) )
        return false;

    return true;
}
//================================================================================================================================================


// 2D case functions =============================================================================================================================
Line_t construct_perpendicular_line_in_plane (const Plane_t& plane, const Line_t& line) {
    return Line_t{plane.normal % line.direction_vec, line.point_on_line};
}

//works properly only if triangles' planes are equal 
bool do_triangles_in_the_same_plane_intersect (const Plane_t& plane, const Triangle_t& first, const Triangle_t& second) {
    
    double first_min, first_max, second_min, second_max;

    for (size_t i0 = 0, i1 = first.nVertices - 1; i0 < first.nVertices; i1 = i0, i0++) {
        Line_t perpendicular = construct_perpendicular_line_in_plane (plane, Line_t{first.points[i1], first.points[i0]}); 

        if (perpendicular.degeneracy == Degeneracy_t::NONE) {                                               
            compute_triangle_projection_on_line_segment ( first, perpendicular,  first_min,  first_max);
            compute_triangle_projection_on_line_segment (second, perpendicular, second_min, second_max);

            if ( first_max < (second_min - EPS) || second_max < (first_min - EPS) )
                return false;
        }
    }

    for (size_t i0 = 0, i1 = second.nVertices - 1; i0 < second.nVertices; i1 = i0, i0++) {
        Line_t perpendicular = construct_perpendicular_line_in_plane (plane, Line_t{second.points[i1], second.points[i0]});

        if (perpendicular.degeneracy == Degeneracy_t::NONE) {
            compute_triangle_projection_on_line_segment ( first, perpendicular,  first_min,  first_max);
            compute_triangle_projection_on_line_segment (second, perpendicular, second_min, second_max);

            if ( first_max < (second_min - EPS) || second_max < (first_min - EPS) )
                return false;
        }
    }

    return true;
}
//================================================================================================================================================


// degeneration case functions ===================================================================================================================

bool select_and_run_algo_for_degenerated_triangles (const Triangle_t& T0, const Triangle_t& T1) {
    
    if (T0.degeneracy == Degeneracy_t::INVALID || T1.degeneracy == Degeneracy_t::INVALID)
        return false;
    
    switch (T0.degeneracy) {

        case Degeneracy_t::NONE: {
            switch (T1.degeneracy) {
                case Degeneracy_t::LINE_SEGMENT: 
                    return do_line_segment_and_triangle_intersect (T1, T0);

                case Degeneracy_t::POINT: 
                    return do_point_and_triangle_intersect (T1.points[0], T0);
                
                default:
                    break;
            }
            break;
        }
        case Degeneracy_t::LINE_SEGMENT: {
            switch (T1.degeneracy) {
                case Degeneracy_t::NONE: 
                    return do_line_segment_and_triangle_intersect (T0, T1);

                case Degeneracy_t::LINE_SEGMENT: 
                    return do_line_segments_intersect (convert_to_line_segment(T0), convert_to_line_segment(T1));

                case Degeneracy_t::POINT: {
                    Line_segment_t segment = convert_to_line_segment(T0); 
                    return ( (Vector_t{T1.points[0]} - Vector_t{segment.p0}).is_collinear_to(Vector_t{T1.points[0]} - Vector_t{segment.p1}) );
                }
                default:
                    break;
            }
            break;
        }
        case Degeneracy_t::POINT: {
            switch (T1.degeneracy) {
                case Degeneracy_t::NONE: 
                    return do_point_and_triangle_intersect (T0.points[0], T1);
                
                case Degeneracy_t::LINE_SEGMENT: {
                    Line_segment_t segment = convert_to_line_segment(T1);
                    return ( (Vector_t{T0.points[0]} - Vector_t{segment.p0}).is_collinear_to(Vector_t{T0.points[0]} - Vector_t{segment.p1}) );
                }
                case Degeneracy_t::POINT: 
                    return (T0.points[0] == T1.points[0]);
                
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }

    return false;

}

bool do_line_segment_and_triangle_intersect (const Triangle_t& degenerated_to_segment, const Triangle_t& triangle) {
    
    Line_t segment_line = Line_t {convert_to_line_segment(degenerated_to_segment)};
    
    double t, u, v, denom;
    Vector_t V01 = Vector_t{triangle.points[1]} - Vector_t{triangle.points[0]};
    Vector_t V02 = Vector_t{triangle.points[2]} - Vector_t{triangle.points[0]};
    
    Vector_t p = segment_line.direction_vec % V02;
    
    if (p.degeneracy == Degeneracy_t::NONE)
        denom = p * V01;
    else if (p.degeneracy == Degeneracy_t::NULL_VECTOR) {
        Plane_t triangle_plane{triangle.points[0], triangle.points[1], triangle.points[2]};
        if ( equal_eps(signed_distance(degenerated_to_segment.points[0], triangle_plane), 0.0) &&
             equal_eps(signed_distance(degenerated_to_segment.points[1], triangle_plane), 0.0) && 
             equal_eps(signed_distance(degenerated_to_segment.points[2], triangle_plane), 0.0) 
           )
            return do_triangles_in_the_same_plane_intersect (triangle_plane, degenerated_to_segment, triangle);
    }
    else
        return false;

    if (equal_eps (denom, 0.0))
        return false;
    else
        denom = 1 / denom;

    Vector_t s = segment_line.point_on_line - Vector_t{triangle.points[0]};
    u = denom * (p * s);
    if ( u < (0.0 - EPS) || u > (1.0 + EPS) )
        return false;
    
    Vector_t q = s % V01;
    v = denom * (q * segment_line.direction_vec);
    if ( v < (0.0 - EPS) || v > (1.0 + EPS) )
        return false;

    if (u + v > 1.0 + EPS)
        return false;
    
    t = denom * (q * V02);

    if ( t < (0.0 - EPS) || t > (1.0 + EPS) ) 
        return false;
    
    return true;
}

//using barycentric coords
bool do_point_and_triangle_intersect (const Point_t& point, const Triangle_t& triangle) {
    
    double doubled_triangle_area = sqrt( ( (Vector_t{triangle.points[1]} - Vector_t{triangle.points[0]}) %
                                           (Vector_t{triangle.points[2]} - Vector_t{triangle.points[0]})   ).squared_length()
                                        );
    
    double alpha = sqrt( ( (Vector_t{triangle.points[1]} - Vector_t{point}) %
                            (Vector_t{triangle.points[2]} - Vector_t{point})   ).squared_length()
                        ) / doubled_triangle_area;
    if ( alpha < (0.0 - EPS) || alpha > (1.0 + EPS) )
        return false;

    double beta  = sqrt( ( (Vector_t{triangle.points[2]} - Vector_t{point}) %
                            (Vector_t{triangle.points[0]} - Vector_t{point})   ).squared_length()
                        ) / doubled_triangle_area;
    if ( beta  < (0.0 - EPS) || beta  > (1.0 + EPS) )
        return false;

    double gamma = sqrt( ( (Vector_t{triangle.points[0]} - Vector_t{point}) %
                            (Vector_t{triangle.points[1]} - Vector_t{point})   ).squared_length()
                        ) / doubled_triangle_area;
    if ( gamma < (0.0 - EPS) || gamma > (1.0 + EPS) )
        return false;
    
    if (!equal_eps(alpha + beta + gamma, 1.0))
        return false;

    return true;   
}   

bool do_line_segments_intersect (const Line_segment_t& seg0, const Line_segment_t& seg1) {

    Line_t line_0  = Line_t{seg0};
    Line_t line_1  = Line_t{seg1};

    double s, t, distance;

    Vector_t u = line_0.point_on_line - line_1.point_on_line;
    double a   = line_0.direction_vec * line_0.direction_vec;
    double b   = line_0.direction_vec * line_1.direction_vec;
    double c   = line_1.direction_vec * line_1.direction_vec;
    double d   = line_0.direction_vec * u;
    double e   = line_1.direction_vec * u;
    double f   = u * u;

    double det = a*c - b*b;
    
    if (equal_eps(det, 0.0)) {  
        s = 0.0;
        
        if (b > c) 
            t = d / b;
        else
            t = e / c;

        distance = f - t * e;

        if (equal_eps(distance, 0.0)) {
            /*double param_0 = ((Vector_t{seg1.p0} - line_0.point_on_line) * line_0.direction_vec) / (line_0.direction_vec.squared_length());
            double param_1 = ((Vector_t{seg1.p1} - line_0.point_on_line) * line_0.direction_vec) / (line_0.direction_vec.squared_length());

            double seg1_min, seg1_max = param_0;

            (param_0 < param_1) ? : seg1_max = param1, seg1_min = param_1;*/
            

            if ( ((e + b) / c) < (0.0 - EPS) || t > (1.0 + EPS) )
                return false;
            
            return true;
        }
    }

    else {
        s = (b*e - c*d) / det;
        t = (a*e - b*d) / det; 

        distance = s * (a*s - b*t + 2.0*d) - t * (b*s - c*t + 2.0*e) + f;

        if (equal_eps(distance, 0.0)) {
            if ( t < (0.0 - EPS) || t > (1.0 + EPS) || s < (0.0 - EPS) || s > (1.0 + EPS) )
                return false;
            else
                return true;
        }
    }

    return false;
}

Line_segment_t convert_to_line_segment (const Triangle_t& triangle) {
    
    Line_t line = Line_t{triangle.points[0], triangle.points[1]};

    if (line.degeneracy == Degeneracy_t::POINT)
        return Line_segment_t {triangle.points[0], triangle.points[2]};
    
    double param = ((Vector_t{triangle.points[2]} - Vector_t{triangle.points[0]}) * line.direction_vec) / line.direction_vec.squared_length();

    if (param < (0.0 - EPS)) 
        return Line_segment_t{triangle.points[1], triangle.points[2]};
    else if (param > (1.0 + EPS))
        return Line_segment_t{triangle.points[0], triangle.points[2]};
    
    return Line_segment_t{triangle.points[0], triangle.points[1]};
}

} //geometry