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
//////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <catch2/catch_all.hpp>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/details_types/s_load_order_read_error.hpp"
#include "luyamlman/error/s_error.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

TEST_CASE(
    "luyamlman::error::s_error: Consolidate just one error",
    "[luyamlman][error][s_error][consolidate_errors]"
)
{
    using luyamlman::error::s_error;
    using luyamlman::error::v_error_details;
    using luyamlman::error_details_types::s_allocation_failure;

    s_error error( v_error_details{ s_allocation_failure{} } );

    REQUIRE( error.size() == 1 );
    error.consolidate_errors();
    REQUIRE( error.size() == 1 );
}

TEST_CASE(
    "luyamlman::error::s_error: consolidate errors - one nested error",
    "[luyamlman][error][s_error][consolidate_errors]"
)
{
    using namespace luyamlman::literals;

    using luyamlman::error::s_error;
    using luyamlman::error::v_error_details;
    using luyamlman::error_details_types::s_allocation_failure;
    using luyamlman::error_details_types::s_load_order_read_error;

    s_error error( v_error_details{
        s_load_order_read_error{
                                .m_code        = s_load_order_read_error::e_code::duplicate_plugin,
                                .m_line_number = 42,
                                .m_plugin_name = "Fun.esp"_esp
        }
    } );

    s_error nested_error( v_error_details{
        s_load_order_read_error{
                                .m_code        = s_load_order_read_error::e_code::duplicate_plugin,
                                .m_line_number = 43,
                                .m_plugin_name = "Fun2.esp"_esp
        }
    } );

    nested_error.insert_additional_error( s_error( v_error_details{
        s_load_order_read_error{
                                .m_code        = s_load_order_read_error::e_code::duplicate_plugin,
                                .m_line_number = 44,
                                .m_plugin_name = "Fun3.esp"_esp
        }
    } ) );
    nested_error.insert_additional_error( s_error( v_error_details{
        s_load_order_read_error{
                                .m_code        = s_load_order_read_error::e_code::duplicate_plugin,
                                .m_line_number = 45,
                                .m_plugin_name = "Fun4.esp"_esp
        }
    } ) );

    error.insert_additional_error( s_error( v_error_details{
        s_load_order_read_error{
                                .m_code        = s_load_order_read_error::e_code::duplicate_plugin,
                                .m_line_number = 46,
                                .m_plugin_name = "Fun5.esp"_esp
        }
    } ) );

    error.insert_additional_error( std::move( nested_error ) );

    REQUIRE( error.size() == 3 );

    auto it = error.begin();

    CHECK(
        std::get<s_load_order_read_error>( it->details() ).m_line_number == 46
    );
    ++it;
    CHECK(
        std::get<s_load_order_read_error>( it->details() ).m_line_number == 43
    );

    error.consolidate_errors();
    REQUIRE( error.size() == 5 );

    it = error.begin();
    CHECK(
        std::get<s_load_order_read_error>( it->details() ).m_line_number == 46
    );
    ++it;
    CHECK(
        std::get<s_load_order_read_error>( it->details() ).m_line_number == 43
    );
    ++it;
    CHECK(
        std::get<s_load_order_read_error>( it->details() ).m_line_number == 44
    );
    ++it;
    CHECK(
        std::get<s_load_order_read_error>( it->details() ).m_line_number == 45
    );
}
