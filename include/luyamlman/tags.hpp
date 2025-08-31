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
namespace luyamlman::tags {

/**
 * @struct s_default
 * @brief The default tag type for arena_allocator and other allocators.
 */
struct s_default;

/**
 * @struct s_error_list
 * @brief Tag type for error list allocator.
 */
struct s_error_list;

/**
 * @struct s_load_order_history_strings
 * @brief Tag type for load order history char allocator.
 */
struct s_load_order_history_strings;

/**
 * @struct s_load_order_strings
 * @brief Tag type for load order char allocator.
 */
struct s_load_order_strings;

/**
 * @struct s_load_order_history_vector
 * @brief Tag type for load order history t_plugin_name vector allocator.
 */
struct s_load_order_history_vector;

/**
 * @struct s_load_order_vector
 * @brief Tag type for load order t_plugin_name vector allocator.
 */
struct s_load_order_vector;

/**
 * @struct s_plugin_name_set
 * @brief Tag type for plugin name set allocator.
 */
struct s_plugin_name_set;

//
// Test Tags...
//

//! Test Tag 01
struct s_test_01;
//! Test Tag 02
struct s_test_02;
//! Test Tag 03
struct s_test_03;
//! Test Tag 04
struct s_test_04;
//! Test Tag 05
struct s_test_05;
//! Test Tag 06
struct s_test_06;
//! Test Tag 07
struct s_test_07;
//! Test Tag 08
struct s_test_08;
//! Test Tag 09
struct s_test_09;

//
// Benchmarking Tags...
//

//! Benchmark Tag 01
struct s_benchmark_01;
//! Benchmark Tag 02
struct s_benchmark_02;
//! Benchmark Tag 03
struct s_benchmark_03;
//! Benchmark Tag 04
struct s_benchmark_04;
//! Benchmark Tag 05
struct s_benchmark_05;
//! Benchmark Tag 06
struct s_benchmark_06;
//! Benchmark Tag 07
struct s_benchmark_07;
//! Benchmark Tag 08
struct s_benchmark_08;
//! Benchmark Tag 09
struct s_benchmark_09;

//
// ADDITIONAL ARENAS
// Although I do not think this is needed at all.
//

//! Arena Tag 2
struct s_arena_02;
//! Arena Tag 3
struct s_arena_03;
//! Arena Tag 4
struct s_arena_04;
//! Arena Tag 5
struct s_arena_05;
//! Arena Tag 6
struct s_arena_06;
//! Arena Tag 7
struct s_arena_07;
//! Arena Tag 8
struct s_arena_08;
//! Arena Tag 9
struct s_arena_09;

} // namespace luyamlman::tags
