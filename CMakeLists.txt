cmake_minimum_required (VERSION 3.27)

include(FetchContent)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

SET(PROJECT_NAME "LootUserListYAMLManager")
SET(CMAKE_CXX_STANDARD 23)
enable_testing()

set(ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(FFI_DIR "${ROOT_DIR}/ffi")
set(INCLUDE_DIR "${ROOT_DIR}/include")
set(SRC_DIR "${ROOT_DIR}/src")
set(MO2_PLUGIN_DIR "${ROOT_DIR}/mo2-plugin/loot_userlist_yaml_manager")

project (${PROJECT_NAME})


# meta_enum
FetchContent_Declare(
    meta_enum
    GIT_REPOSITORY "https://github.com/therocode/meta_enum.git"
    GIT_TAG "master"
)

FetchContent_MakeAvailable(meta_enum)

#
# Compile commands
#
add_custom_target(
    copy-compile-commands ALL
    ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_LIST_DIR}
)


add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(ffi)
