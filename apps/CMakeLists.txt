set (
    APPS
    simplest_triangle_comparison_run
    AABB_triangle_comparison_run
    BSP_triangle_comparison_run
)

set (VISUALS
    visualization_run
)

foreach(APP ${APPS})
    add_subdirectory(${APP})
endforeach()

foreach(VISUAL ${VISUALS})
    add_subdirectory(${VISUAL})
endforeach()

set(APPS "${APPS}" PARENT_SCOPE) 
set(VISUALS "${VISUALS}" PARENT_SCOPE) 

