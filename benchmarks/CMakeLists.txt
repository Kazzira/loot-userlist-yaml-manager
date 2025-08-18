# LOOT USERLIST YAML MAANGER C++ BENCHMARKS

# Using Catch2 for benchmarks...
find_package(Catch2 REQUIRED CONFIG)
find_package(strong_type REQUIRED CONFIG)

# ----------------------------------------------------------------------------
# luyamlman::error::s_error::consolidate_errors
# luyamlman_error_s_error_consolidate_errors_benchmark
# ----------------------------------------------------------------------------
add_executable(
    luyamlman_error_s_error_consolidate_errors_benchmark
    "${ROOT_DIR}/benchmarks/luyamlman_error_s_error_consolidate_errors_benchmark/src/benchmark.cpp"
)

target_include_directories(
    luyamlman_error_s_error_consolidate_errors_benchmark
    PUBLIC
    "${ROOT_DIR}/benchmarks/luyamlman_error_s_error_consolidate_errors_benchmark/include"
)

target_link_libraries(
    luyamlman_error_s_error_consolidate_errors_benchmark
    PRIVATE
    luyamlman
    strong_type::strong_type
    Catch2::Catch2WithMain
)
# ----------------------------------------------------------------------------
