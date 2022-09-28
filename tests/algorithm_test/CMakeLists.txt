set(
    TESTS
    2D_algorithm_test
    degeneration_test
    main_algorithm_test
)

foreach(TEST ${TESTS})
    add_subdirectory(${TEST})    
endforeach()

set (TESTS "${TESTS}" PARENT_SCOPE)