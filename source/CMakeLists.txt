set(
    LIBS
    line
    point
    vector_geom
    plane
    line_segment
    triangle
    AABB
    BSP_tree
    Triangle_intersection_algorithm
)

foreach(LIB ${LIBS})
    add_subdirectory(${LIB})
endforeach()

set(LIBS "${LIBS}" PARENT_SCOPE) 
