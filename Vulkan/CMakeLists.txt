set (
    VULKAN_LIBS
    source
)

foreach(VULKAN_LIB ${VULKAN_LIBS})
    add_subdirectory(${VULKAN_LIB})
endforeach()

set(VULKAN_LIBS "${VULKAN_LIBS}" PARENT_SCOPE) 
