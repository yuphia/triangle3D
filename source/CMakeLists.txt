set(
    LIBS
    line
    point
    vector_geom
    plane
    line_segment
    triangle
    computational_algorithms
)

foreach(LIB ${LIBS})
    add_subdirectory(${LIB})
endforeach()

set(LIBS "${LIBS}" PARENT_SCOPE) 
