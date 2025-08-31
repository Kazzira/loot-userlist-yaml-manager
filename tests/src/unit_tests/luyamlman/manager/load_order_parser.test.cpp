/*
Copyright (C) 2024-2025 Zachary Dakota Meyer. All rights reserved.

This file is part of the LOOT Userlist.yaml Manager project.

LOOT Userlist.yaml Manager is free software: you can redistribute it and/or
modify it under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your option)
any later version.

LOOT Userlist.yaml Manager is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LOOT Userlist.yaml Manager.  If not, see
<http://www.gnu.org/licenses/>.
*/
/////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include <catch2/catch_all.hpp>

/////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/details_types/s_load_order_read_error.hpp"
#include "luyamlman/manager/s_data.hpp"
#include "luyamlman/overloads.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

TEST_CASE(
    "luyamlman:manager: Test parsing a load order file",
    "[luyamlman][manager][load_order_parser]"
)
{
    using namespace luyamlman::literals;

    auto load_order_file_path
        = std::filesystem::path( TEST_DATA_DIR ) / "load_order1.txt";

    auto load_order_file_path_str = load_order_file_path.string();

    luyamlman::manager::s_data<> data;

    auto result = data.parse_load_order_file( load_order_file_path_str );

    REQUIRE( result );

    REQUIRE( data.load_order().size() == 2 );
    REQUIRE( data.load_order()[0] == "Skyrim.esm"_esp );
    REQUIRE( data.load_order()[1] == "Update.esm"_esp );
}

TEST_CASE(
    "luyamlman:manager: Test parsing a load order file with duplicates",
    "[luyamlman][manager][load_order_parser]"
)
{
    using namespace luyamlman::literals;

    using luyamlman::error_details_types::s_load_order_read_error;

    auto load_order_file_path
        = std::filesystem::path( TEST_DATA_DIR ) / "load_order2.txt";
    auto load_order_file_path_str = load_order_file_path.string();
    luyamlman::manager::s_data<> data;
    auto result = data.parse_load_order_file( load_order_file_path_str );

    REQUIRE( !result );

    // Only one error.
    CHECK( result.error().size() == 1 );

    // Make sure the details is correct.
    REQUIRE_NOTHROW(
        std::get<luyamlman::error_details_types::s_load_order_read_error>(
            result.error().details()
        )
    );

    auto& error_details
        = std::get<luyamlman::error_details_types::s_load_order_read_error>(
            result.error().details()
        );

    CHECK(
        error_details.m_code
        == s_load_order_read_error::e_code::duplicate_plugin
    );
    CHECK( error_details.m_line_number == 7 );
    CHECK( error_details.m_plugin_name == "Plugin3.esp"_esp );
}

TEST_CASE(
    "luyamlman:manager: Parse load order with multiple duplicates",
    "[luyamlman][manager][load_order_parser]"
)
{
    using namespace luyamlman::literals;

    using luyamlman::error_details_types::s_load_order_read_error;

    auto load_order_file_path
        = std::filesystem::path( TEST_DATA_DIR ) / "load_order3.txt";
    auto load_order_file_path_str = load_order_file_path.string();
    luyamlman::manager::s_data<> data;
    auto result = data.parse_load_order_file( load_order_file_path_str );

    REQUIRE( !result );

    // Multiple errors.
    CHECK( result.error().size() == 3 );

    auto perform_assertions = []( const luyamlman::error::s_error<>& a_error,
                                  uint32_t                        a_line_number,
                                  luyamlman::types::t_plugin_name a_plugin_name,
                                  s_load_order_read_error::e_code a_code )
    {
        std::visit(
            luyamlman::overloads{
                []( const luyamlman::error_details_types::
                        s_allocation_failure& )
                {
                    FAIL( "Unexpected allocation failure error." );
                },
                []( const luyamlman::error_details_types::s_filesystem_error& )
                {
                    FAIL( "Unexpected filesystem error." );
                },
                [&]( const luyamlman::error_details_types::
                         s_load_order_read_error& error_details )
                {
                    CHECK( error_details.m_code == a_code );
                    CHECK( error_details.m_line_number == a_line_number );
                    CHECK( error_details.m_plugin_name == a_plugin_name );
                }
            },
            a_error.details()
        );
    };

    perform_assertions(
        result.error(),
        8,
        "Funtimes420.esp"_esp,
        s_load_order_read_error::e_code::duplicate_plugin
    );

    auto it = result.error().begin();

    perform_assertions(
        *it,
        10,
        "HalfLife3.esm"_esp,
        s_load_order_read_error::e_code::duplicate_plugin
    );

    ++it;

    perform_assertions(
        *it,
        11,
        "Funtimes420.esp"_esp,
        s_load_order_read_error::e_code::duplicate_plugin
    );
}
