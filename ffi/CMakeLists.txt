set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(
    LootUserListYAMLManagerFFI
    SHARED
    "${ROOT_DIR}/ffi/src/loot_userlist_yaml_manager_ffi.cpp"
)

target_include_directories(
    LootUserListYAMLManagerFFI
    PUBLIC
    "${ROOT_DIR}/ffi/include"
)

target_include_directories(
    LootUserListYAMLManagerFFI
    PRIVATE
    "${ROOT_DIR}/include"
)
target_link_libraries(
    LootUserListYAMLManagerFFI
    PUBLIC
    luyamlman
)
