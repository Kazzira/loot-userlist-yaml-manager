#pragma once
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
#include <set>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/s_error.hpp"
#include "luyamlman/types/std_internals.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

//////////////////////////////////////////////////////////////////////////////
// BENCHMARK INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "benchmark/aliases.hpp"

namespace benchmark {

inline void
initialize_allocators() noexcept
{
    using luyamlman::types::t_plugin_name;

    constexpr size_t k_plugin_name_string_allocator_block_size = 4000;
    constexpr size_t k_plugin_name_vector_allocator_size       = 200;
    constexpr size_t k_plugin_name_vector_allocator_block_size
        = 200 * sizeof( t_plugin_name );
    constexpr size_t k_plugin_name_set_allocator_size = 200;
    constexpr size_t k_plugin_name_set_allocator_block_size
        = 200
        * ( sizeof( luyamlman::types::t_std_set_tree_node<t_plugin_name> ) );
    constexpr size_t k_plugin_name_single_string_allocator_block_size = 250;
    constexpr size_t k_error_list_allocator_size                      = 8;
    constexpr size_t k_error_list_allocator_block_size
        = k_error_list_allocator_size
        * sizeof( luyamlman::error::s_error<t_error_list_allocator> );

    constexpr size_t k_total_allocator_block_size
        = k_plugin_name_string_allocator_block_size
        + k_plugin_name_vector_allocator_block_size
        + k_plugin_name_set_allocator_block_size
        + k_plugin_name_single_string_allocator_block_size
        + k_error_list_allocator_block_size;

    t_arena::singleton::get_instance( k_total_allocator_block_size + 2400 );
    t_plugin_name_vector_allocator<t_plugin_name>::intitialize(
        k_plugin_name_vector_allocator_size
    );
    t_plugin_name_string_allocator<char>::intitialize(
        k_plugin_name_string_allocator_block_size
    );

    t_plugin_set_allocator<luyamlman::types::t_std_set_tree_node<
        t_plugin_name>>::intitialize( k_plugin_name_set_allocator_size );
    t_plugin_name_single_string_allocator<char>::intitialize(
        k_plugin_name_single_string_allocator_block_size
    );
    t_error_list_allocator<luyamlman::error::s_error<t_error_list_allocator>>::
        intitialize( k_error_list_allocator_size );
}

} // namespace benchmark
