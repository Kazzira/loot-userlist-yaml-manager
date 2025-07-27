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
#include <fstream>
#include <string>
#include <string_view>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/details_types/s_allocation_failure.hpp"
#include "luyamlman/error/details_types/s_filesystem_error.hpp"
#include "luyamlman/error/s_error.hpp"

namespace luyamlman::manager {

result<std::vector<std::string>>
parse_load_order_file(
    [[maybe_unused]] std::string_view a_load_order_file_path
)
{
    using luyamlman::error::s_error;
    using luyamlman::error_details_types::s_allocation_failure;
    using luyamlman::error_details_types::s_filesystem_error;

    std::vector<std::string> load_order;
    std::ifstream            load_order_file( a_load_order_file_path.data() );

    if( !load_order_file.is_open() )
    {
        return std::unexpected(
            s_error( s_filesystem_error{ a_load_order_file_path } )
        );
    }

    std::string line;

    while( std::getline( load_order_file, line ) )
    {
        if( line.empty() || line[0] == '#' )
        {
            continue; // Skip empty lines and comments.
        }

        // Trim whitespace from the line.
        line.erase( 0, line.find_first_not_of( " \t" ) );
        line.erase( line.find_last_not_of( " \t" ) + 1 );

        if( !line.empty() )
        {
            // Add the valid line to the load order.
            load_order.push_back( std::move( line ) );
        }
    }

    return load_order;
}

} // namespace luyamlman::manager
