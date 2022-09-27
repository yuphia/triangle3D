set(
    LIBS
    line
    point
    vector
    plane
    line_segment
    triangle
)

foreach(LIB ${LIBS})
    add_subdirectory(${LIB})
endforeach()

set(LIBS "${LIBS}" PARENT_SCOPE) 
