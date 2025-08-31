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
#include "luyamlman/memory/arena_allocator.hpp"
#include "luyamlman/memory/linear_allocator.hpp"
#include "luyamlman/tags.hpp"

namespace benchmark {
using t_arena
    = luyamlman::memory::arena_allocator<luyamlman::tags::s_benchmark_01>;

template <typename T>
using t_plugin_set_allocator = luyamlman::memory::linear_allocator<
    luyamlman::tags::s_benchmark_01,
    luyamlman::tags::s_plugin_name_set,
    luyamlman::memory::e_usage::multiple>::allocator<T>;

template <typename T>
using t_plugin_name_vector_allocator = luyamlman::memory::linear_allocator<
    luyamlman::tags::s_benchmark_01,
    luyamlman::tags::s_load_order_vector,
    luyamlman::memory::e_usage::multiple>::allocator<T>;

template <typename T>
using t_plugin_name_string_allocator = luyamlman::memory::linear_allocator<
    luyamlman::tags::s_benchmark_01,
    luyamlman::tags::s_load_order_strings,
    luyamlman::memory::e_usage::multiple>::allocator<T>;

template <typename T>
using t_plugin_name_single_string_allocator
    = luyamlman::memory::linear_allocator<
        luyamlman::tags::s_benchmark_01,
        luyamlman::tags::s_load_order_strings,
        luyamlman::memory::e_usage::single>::allocator<T>;

template <typename T>
using t_error_list_allocator = luyamlman::memory::linear_allocator<
    luyamlman::tags::s_benchmark_01,
    luyamlman::tags::s_error_list,
    luyamlman::memory::e_usage::multiple>::allocator<T>;

} // namespace benchmark
