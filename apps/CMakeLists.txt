set (
    APPS
    simplest_triangle_comparison_run
    AABB_triangle_comparison_run
)

foreach(APP ${APPS})
    add_subdirectory(${APP})
endforeach()

set(APPS "${APPS}" PARENT_SCOPE) 
