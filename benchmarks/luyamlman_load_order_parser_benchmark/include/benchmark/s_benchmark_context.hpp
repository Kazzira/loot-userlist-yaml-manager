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

enum class e_context_option
{
    no_arena,
    arena
};

template <e_context_option AOption>
struct s_benchmark_context
{
        ~s_benchmark_context()
        {
            using luyamlman::types::t_plugin_name;
            using luyamlman::types::t_std_set_tree_node;

            if constexpr( AOption == e_context_option::arena )
            {
                t_arena::singleton::get_instance().reset();

                t_plugin_set_allocator<
                    t_std_set_tree_node<t_plugin_name>>::reset_allocator();

                t_plugin_name_vector_allocator<t_plugin_name>::reset_allocator(
                );
                t_plugin_name_string_allocator<char>::reset_allocator();
                t_plugin_name_single_string_allocator<char>::reset_allocator();
                t_error_list_allocator<luyamlman::error::s_error<
                    t_error_list_allocator>>::reset_allocator();
            }
            else
            {
                t_plugin_set_allocator<
                    t_std_set_tree_node<t_plugin_name>>::reset_used();
                t_plugin_name_vector_allocator<t_plugin_name>::reset_used();
                t_plugin_name_string_allocator<char>::reset_used();
                t_plugin_name_single_string_allocator<char>::reset_used();
                t_error_list_allocator<luyamlman::error::s_error<
                    t_error_list_allocator>>::reset_used();
            }
        }
};

} // namespace benchmark
