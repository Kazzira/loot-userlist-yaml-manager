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
// STANDARD LIBRARY INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include <cstdint>

/////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include <catch2/catch_all.hpp>

/////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/s_error.hpp"

/////////////////////////////////////////////////////////////////////////////
// BENCHMARK INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include "benchmark/types/t_child_count.hpp"
#include "benchmark/types/t_depth.hpp"

namespace {

luyamlman::error::s_error
                          create_test_error() noexcept;

luyamlman::error::s_error create_test_error_nested(
    benchmark::types::t_depth,
    benchmark::types::t_children
);

void
walk_through_all_errors( const luyamlman::error::s_error& error ) noexcept;

} // namespace

TEST_CASE(
    "benchmark: Test consolidate_errors() performance",
    "[benchmark][consolidate_errors_performance]"
)
{
    using namespace benchmark::types::literals;

    using luyamlman::error::s_error;
    using luyamlman::error_details_types::s_load_order_read_error;

    s_error main_error = create_test_error_nested( 5_depth, 5_children );
    s_error deep_error = create_test_error_nested( 15_depth, 2_children );

    for( size_t _ = 0; _ < 1000; ++_ )
    {
        walk_through_all_errors( main_error );
    }

    BENCHMARK(
        "Consolidate errors with 5 levels of nesting and 5 children per level"
    )
    {
        main_error.consolidate_errors();
        return main_error;
    };

    for( size_t _ = 0; _ < 1000; ++_ )
    {
        walk_through_all_errors( deep_error );
    }

    BENCHMARK(
        "Consolidate errors with 15 levels of nesting and 2 children per level"
    )
    {
        deep_error.consolidate_errors();
        return deep_error;
    };
}

namespace {

luyamlman::error::s_error
create_test_error() noexcept
{
    using luyamlman::error::s_error;
    using luyamlman::error_details_types::s_load_order_read_error;

    using e_code = s_load_order_read_error::e_code;

    return s_error{
        s_load_order_read_error{
                                .m_code        = e_code::duplicate_plugin,
                                .m_line_number = 1,
                                .m_plugin_name = "T"
        }
    };
}

luyamlman::error::s_error
create_test_error_nested(
    benchmark::types::t_depth    a_depth,
    benchmark::types::t_children a_number_of_children
)
{
    using namespace benchmark::types::literals;

    using benchmark::types::t_children;
    using benchmark::types::t_depth;
    using luyamlman::error::s_error;
    using luyamlman::error_details_types::s_load_order_read_error;

    s_error error = create_test_error();

    if( a_depth > 0_depth )
    {
        for( auto i = 0_children; i < a_number_of_children; ++i )
        {
            error.insert_additional_error( create_test_error_nested(
                a_depth - 1_depth,
                a_number_of_children
            ) );
        }
    }

    return error;
}

void
walk_through_all_errors(
    const luyamlman::error::s_error& error
) noexcept
{
    using luyamlman::error::s_error;

    // Walk through the main error.
    const s_error* current_error = &error;

    if( !current_error->empty() )
    {
        // If it has additional errors, we will walk through them.
        for( const auto& additional_error : *current_error )
        {
            walk_through_all_errors( additional_error );
        }
    }
}

} // namespace
