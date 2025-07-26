add_executable(
    luyamlman-tests
    "${ROOT_DIR}/tests/src/unit_tests/luyamlman/error/s_error.test.cpp"
)

target_include_directories(
    luyamlman-tests
    PRIVATE
    "${ROOT_DIR}/include"
)

target_include_directories(
    luyamlman-tests
    PRIVATE
    "${ROOT_DIR}/tests/include"
)

find_package(Catch2 REQUIRED CONFIG)

target_link_libraries(
    luyamlman-tests
    PRIVATE
    luyamlman
    Catch2::Catch2WithMain
)
