set (
    TESTS
    vector_geom_functions_test
    triangle_functions_test
    point_functions_test
    plane_functions_test
    line_segment_functions_test
    line_functions_test
    AABB_functions_test
)

foreach (TEST ${TESTS})
    add_subdirectory(${TEST})    
endforeach()

set (CLASS_TESTS "${TESTS}" PARENT_SCOPE)