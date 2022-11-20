
cmake_minimum_required (VERSION 3.14)

project(triangle_proj VERSION 1.0)

find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_program(glslc_executable NAMES glslc HINTS Vulkan::glslc)

file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file).
Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

set (
WARNS
-Wall
-Wextra
-Wpedantic
-Werror
-Waggressive-loop-optimizations
-Wc++0x-compat
-Wc++11-compat
-Wc++14-compat
-Wcast-align
-Wcast-qual
-Wchar-subscripts
-Wconditionally-supported
-Wctor-dtor-privacy
-Wempty-body
-Wformat-nonliteral
-Wformat-security
-Wformat-signedness
-Wformat=2
-Winline
-Wlogical-op
-Wmissing-declarations
-Wnon-virtual-dtor
-Wopenmp-simd
-Woverloaded-virtual
-Wpacked
-Wpointer-arith
-Wredundant-decls
-Wshadow
-Wsign-conversion
-Wsign-promo
-Wstack-usage=16384
-Wstrict-null-sentinel
-Wstrict-overflow=2
-Wsuggest-attribute=noreturn
-Wsuggest-final-methods
-Wsuggest-final-types
-Wsuggest-override
-Wswitch-default
#-Wswitch-enum
-Wsync-nand
-Wundef
-Wunreachable-code
-Wuseless-cast
-Wvariadic-macros
-Wno-literal-suffix
-Wno-missing-field-initializers
-Wno-narrowing
-Wno-old-style-cast
-Wno-varargs
-fcheck-new
-fstack-protector
-fstrict-overflow
-flto-odr-type-merging
-fno-omit-frame-pointer
)

set(
FLAGS 
-fsanitize=address
-fsanitize=alignment
-fsanitize=bool
-fsanitize=bounds
-fsanitize=enum
-fsanitize=float-cast-overflow
-fsanitize=float-divide-by-zero
-fsanitize=integer-divide-by-zero
-fsanitize=leak
-fsanitize=nonnull-attribute
-fsanitize=null
-fsanitize=object-size
-fsanitize=return
-fsanitize=returns-nonnull-attribute
-fsanitize=shift
-fsanitize=signed-integer-overflow
-fsanitize=undefined
-fsanitize=unreachable
-fsanitize=vla-bound
-fsanitize=vptr
-fsized-deallocation
)

add_subdirectory(source)

message (STATUS "\n////////////////")
message (STATUS "Collected LIBS:")
foreach(LIB ${LIBS})
    message (STATUS "   ${LIB}")
endforeach()
message (STATUS "")

foreach(LIB ${LIBS})
    message (STATUS "lib: ${LIB}")

    target_compile_features(${LIB} PRIVATE cxx_std_17)

    #target_link_options(${LIB} PRIVATE "${FLAGS}")
    #target_compile_options(${LIB} PRIVATE "${WARNS};${FLAGS}")

    target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    
    get_property(dirs TARGET ${LIB} PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
    foreach(dir ${dirs})
        message(STATUS "    ${LIB} includes dir = '${dir}'")    
    endforeach()
    message (STATUS "")
endforeach()


foreach(LIB ${LIBS})
    foreach(LIB_TO_LINK ${LIBS})
        if (NOT ${LIB} STREQUAL ${LIB_TO_LINK})
            target_link_libraries(${LIB} PRIVATE ${LIB_TO_LINK})
            endif()
    endforeach()

    get_target_property(OUT ${LIB} LINK_LIBRARIES)
    
    message(STATUS "TO LIB: ${LIB}")

    foreach(LIB_MESSAGE ${OUT})
        message(STATUS "    linked: ${LIB_MESSAGE}")
    endforeach()
    message(STATUS "")        
endforeach()


enable_testing()
find_package (GTest REQUIRED)


add_subdirectory(tests)

message (STATUS "\n////////////////")
message (STATUS "Collected TESTS:")
foreach(TEST ${TESTS})
message (STATUS "   ${TEST}")
endforeach()
message (STATUS "")


foreach (TEST ${TESTS})
    message (STATUS "tests: ${TEST}")

    target_compile_features(${TEST} PRIVATE cxx_std_17)

    #target_link_options(${TEST} PRIVATE "${FLAGS}")
    #target_compile_options(${TEST} PRIVATE "${WARNS};${FLAGS}")
    
    target_include_directories(${TEST} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries (${TEST} PRIVATE ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} pthread)
    target_link_libraries (${TEST} PRIVATE ${LIBS})
    
    get_target_property(OUT ${TEST} LINK_LIBRARIES)
    get_target_property(OUT_OPTIONS ${TEST} LINK_OPTIONS)
    
    foreach(OUT_OPTION ${OUT_OPTIONS})
    message (STATUS "     linked option: ${OUT_OPTION}")
    endforeach()
    
    foreach(LIB ${OUT})
    message(STATUS "    linked: ${LIB}")
    endforeach()
    
    message(STATUS "")
    
endforeach ()

add_subdirectory(apps)
message (STATUS "\n////////////////")
message (STATUS "Collected APPS: ${APPS}")
    
foreach(APP ${APPS})
    message (STATUS "app: ${APP}")

    target_compile_features(${APP} PRIVATE cxx_std_17)

    #target_link_options(${APP} PRIVATE "${FLAGS}")
    #target_compile_options(${APP} PRIVATE "${WARNS};${FLAGS}")

    target_include_directories(${APP} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${APP} PRIVATE ${LIBS})

    get_property(dirs TARGET ${APP} PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
    foreach(dir ${dirs})
        message(STATUS "    ${APP} includes dir = '${dir}'")    
    endforeach()

    get_target_property(OUT ${APP} LINK_LIBRARIES)
    
    foreach(LIB ${OUT})
        message(STATUS "    linked: ${LIB}")
    endforeach()

    message (STATUS "")
endforeach()
 
#///////////////////////////////////////////////////////////////////////////////////////

add_subdirectory(Vulkan)

foreach(VULKAN_LIB ${VULKAN_LIBS})
    target_compile_features(${VULKAN_LIB} PRIVATE cxx_std_17)

    target_include_directories(${VULKAN_LIB} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Vulkan/include ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${VULKAN_LIB} PRIVATE glm::glm glfw ${Vulkan_LIBRARIES}) 
endforeach()


file(GLOB_RECURSE GLSL_SOURCE_FILES
  "Vulkan/shaders/*.frag"
  "Vulkan/shaders/*.vert"
)
 
foreach(GLSL ${GLSL_SOURCE_FILES})
    get_filename_component(FILE_NAME ${GLSL} NAME)
    set(SPIRV "../Vulkan/shaders/${FILE_NAME}.spv")
    add_custom_command(
        OUTPUT ${SPIRV}
        COMMAND ${glslc_executable} ${GLSL} -o ${SPIRV}
        DEPENDS ${GLSL})
    list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)
 
add_custom_target(
    Shaders
    DEPENDS ${SPIRV_BINARY_FILES}
)

message (STATUS "\n////////////////")
message (STATUS "Collected VISUAL_APPS: ${VISUALS}")

foreach(VISUAL ${VISUALS})
    message (STATUS "visual_app: ${VISUAL}")

    target_compile_features(${VISUAL} PRIVATE cxx_std_17)

    add_dependencies(${VISUAL} Shaders)

    target_include_directories (${VISUAL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Vulkan/include ${Vulkan_INCLUDE_DIRS})
    target_link_libraries(${VISUAL} PRIVATE glm::glm glfw ${Vulkan_LIBRARIES})
    target_link_libraries(${VISUAL} PRIVATE ${VULKAN_LIBS})      
    
    
    
    #target_link_options(${VISUAL} PRIVATE "${FLAGS}")
    #target_compile_options(${VISUAL} PRIVATE "${WARNS};${FLAGS}")

    target_include_directories(${VISUAL} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_link_libraries(${VISUAL} PRIVATE ${LIBS})

    get_property(dirs TARGET ${VISUAL} PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
    foreach(dir ${dirs})
        message(STATUS "    ${VISUAL} includes dir = '${dir}'")    
    endforeach()

    get_target_property(OUT ${VISUAL} LINK_LIBRARIES)
    
    foreach(LIB ${OUT})
        message(STATUS "    linked: ${LIB}")
    endforeach()

    message (STATUS "")
endforeach()

