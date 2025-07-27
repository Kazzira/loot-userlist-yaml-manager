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
#include "luyamlman/manager/load_order_parser.hpp"

TEST_CASE(
    "luyamlman:manager: Test parsing a load order file",
    "[luyamlman][manager][load_order_parser]"
)
{
    auto load_order_file_path
        = std::filesystem::path( TEST_DATA_DIR ) / "load_order1.txt";

    auto load_order_file_path_str = load_order_file_path.string();

    auto result
        = luyamlman::manager::parse_load_order_file( load_order_file_path_str );

    REQUIRE( result );
    REQUIRE( result->size() == 2 );
    REQUIRE( result->at( 0 ) == "Skyrim.esm" );
    REQUIRE( result->at( 1 ) == "Update.esm" );
}
