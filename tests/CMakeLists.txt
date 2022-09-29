set(
    TEST_DIRS
    algorithm_test
    class_test
    common_test
)

foreach(TEST_DIR ${TEST_DIRS})
    add_subdirectory(${TEST_DIR})
endforeach()

list(APPEND TESTS ${CLASS_TESTS})
list(APPEND TESTS common_test)

set(TESTS "${TESTS}" PARENT_SCOPE)