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
#include <filesystem>

/////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include <catch2/catch_all.hpp>

/////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/s_error.hpp"
#include "luyamlman/manager/load_order_parser.hpp"
#include "luyamlman/manager/s_data.hpp"
#include "luyamlman/memory/arena_allocator.hpp"
#include "luyamlman/tags.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

/////////////////////////////////////////////////////////////////////////////
// BENCHMARK INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include "benchmark/aliases.hpp"
#include "benchmark/benchmark_allocator_initializer.hpp"
#include "benchmark/s_benchmark_context.hpp"

static const std::string k_file_path
    = ( std::filesystem::path( TEST_DATA_DIR ) / "load_order4.txt" ).string();

TEST_CASE(
    "parse_load_order: Using standard allocator",
    "[standard_allocator]"
)
{
    using luyamlman::manager::parse_load_order_file;

    // Pre-parse to avoid measuring one-time setup costs.
    (void)parse_load_order_file( k_file_path );

    BENCHMARK( "parse_load_order_file" )
    {
        return parse_load_order_file( k_file_path );
    };
}

TEST_CASE(
    "parse_load_order: Using custom allocator",
    "[custom_allocator]"
)
{
    using benchmark::e_context_option;

    auto parse_load_order_file = [&]()
    {
        using luyamlman::manager::parse_load_order_file;
        benchmark::s_benchmark_context<e_context_option::no_arena> ctx;

        auto load_order = parse_load_order_file<
            benchmark::t_plugin_name_vector_allocator,
            benchmark::t_plugin_name_string_allocator,
            benchmark::t_plugin_name_single_string_allocator,
            benchmark::t_plugin_set_allocator,
            benchmark::t_error_list_allocator>( k_file_path );

        char cc{ 0 };

        for( auto _ = 0; _ < 10; ++_ )
        {
            for( const auto& plugin_name : *load_order )
            {
                for( const auto& c : plugin_name.value_of() )
                {
                    cc = c == '\0' ? cc : c;
                }
            }
        }

        return load_order;
    };

    benchmark::initialize_allocators();
    benchmark::s_benchmark_context<e_context_option::arena> gctx;

    // Pre-parse to avoid measuring one-time setup costs.
    //(void)parse_load_order_file();

    BENCHMARK( "parse_load_order_file" )
    {
        return parse_load_order_file();
    };
}
