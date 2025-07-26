add_library(
    luyamlman
    STATIC
    "${ROOT_DIR}/src/error/s_error.cpp"
)

add_dependencies(
    luyamlman
    meta_enum
)

target_link_libraries(
    luyamlman
    PUBLIC
    meta_enum
)

target_include_directories(
    luyamlman
    PUBLIC
    "${ROOT_DIR}/include"
)