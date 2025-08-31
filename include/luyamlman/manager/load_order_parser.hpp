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
// STANDARD LIBRARY INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <string>
#include <string_view>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/s_error.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

namespace luyamlman::manager {

/**
 * @brief Parses a load order file and returns a vector of plugin names.
 *
 * This function reads a load order file, extracts plugin names, and ensures
 * that each plugin name is unique. It trims whitespace from each line
 * and skips empty lines. If a duplicate plugin name is found, it
 * returns an error with details about the duplicate plugin and its line number.
 * If the file cannot be opened, it returns an error indicating a filesystem
 * issue.
 *
 * @param a_load_order_file_path The path to the load order file to be parsed.
 * @return A result containing a vector of unique plugin names if successful, or
 * an error if the file could not be opened or if a duplicate plugin was found.
 */
template <
    template <class> typename AVectorAllocator         = std::allocator,
    template <class> typename ACharAllocator           = std::allocator,
    template <class> typename ATempStringCharAllocator = std::allocator,
    template <class> typename AStringViewSetAllocator  = std::allocator,
    template <class> typename AErrorListAllocator      = std::allocator>
result<
    std::vector<
        luyamlman::types::t_plugin_name,
        AVectorAllocator<luyamlman::types::t_plugin_name>>,
    AErrorListAllocator>
parse_load_order_file( std::string_view a_load_order_file_path );

} // namespace luyamlman::manager

#include "luyamlman/manager/load_order_parser.tpp"
