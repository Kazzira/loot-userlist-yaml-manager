add_library(
    luyamlman
    STATIC
    "${ROOT_DIR}/src/error/s_error.cpp"
    "${ROOT_DIR}/src/manager/load_order_parser.cpp"
    "${ROOT_DIR}/src/manager/s_manager.cpp"
    "${ROOT_DIR}/src/raii/s_application_global_allocator_handler.cpp"
    "${ROOT_DIR}/src/types/t_loot_group_name.cpp"
    "${ROOT_DIR}/src/types/t_plugin_name.cpp"
)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(strong_type CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

add_dependencies(
    luyamlman
    meta_enum
)

target_link_libraries(
    luyamlman
    PUBLIC
    meta_enum
    nlohmann_json::nlohmann_json
    strong_type::strong_type
    yaml-cpp::yaml-cpp
)


target_include_directories(
    luyamlman
    PUBLIC
    "${ROOT_DIR}/include"
)

target_include_directories(
    luyamlman
    PRIVATE
    "${ROOT_DIR}/src"
)
