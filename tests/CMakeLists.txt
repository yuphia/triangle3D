set(
    TEST_DIRS
    algorithm_test
    vector_functions_test
)

foreach(TEST_DIR ${TEST_DIRS})
    add_subdirectory(${TEST_DIR})
endforeach()

list(APPEND TESTS vector_functions_test)
set(TESTS "${TESTS}" PARENT_SCOPE)