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
