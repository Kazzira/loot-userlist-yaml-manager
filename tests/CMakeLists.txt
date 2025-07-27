add_executable(
    luyamlman-tests
    "${ROOT_DIR}/tests/src/luyamlman_tests/ffi/ffi_wrapper.cpp"

    "${ROOT_DIR}/tests/src/unit_tests/luyamlman/error/s_error.test.cpp"
    "${ROOT_DIR}/tests/src/unit_tests/luyamlman/manager/load_order_parser.test.cpp"

    "${ROOT_DIR}/tests/src/unit_tests/ffi/ffi.test.cpp"
)

add_custom_command(
    TARGET luyamlman-tests
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:LootUserListYAMLManagerFFI>
    $<TARGET_FILE_DIR:luyamlman-tests>
)

target_include_directories(
    luyamlman-tests
    PRIVATE
    "${ROOT_DIR}/include"
)

target_include_directories(
    luyamlman-tests
    PRIVATE
    "${ROOT_DIR}/ffi/include"
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
    LootUserListYAMLManagerFFI
    Catch2::Catch2WithMain
)

include(CTest)
include(Catch)
catch_discover_tests(luyamlman-tests)

add_custom_command(
  OUTPUT _run-luyamlman-tests-completed
  COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure
  COMMAND cmake -E touch _run-luyamlman-tests-completed
  DEPENDS luyamlman-tests luyamlman LootUserListYAMLManagerFFI
)

add_custom_target(run-luyamlman-tests ALL
  DEPENDS _run-luyamlman-tests-completed
)

