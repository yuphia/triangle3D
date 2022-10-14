set(
    LIBS
    BSP_tree
    Triangle_intersection_algorithm
)

foreach(LIB ${LIBS})
    add_subdirectory(${LIB})
endforeach()

set(LIBS "${LIBS}" PARENT_SCOPE) 
