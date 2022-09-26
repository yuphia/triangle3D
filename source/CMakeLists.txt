set(
    LIBS
    line
    point
    vector
    plane
)

foreach(LIB ${LIBS})
    add_subdirectory(${LIB})
endforeach()

set(LIBS "${LIBS}" PARENT_SCOPE) 
