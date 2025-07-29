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
#include <set>
#include <string>
#include <string_view>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/details_types/s_allocation_failure.hpp"
#include "luyamlman/error/details_types/s_filesystem_error.hpp"
#include "luyamlman/error/details_types/s_load_order_read_error.hpp"
#include "luyamlman/error/s_error.hpp"

namespace luyamlman::manager {

result<std::vector<std::string>>
parse_load_order_file(
    std::string_view a_load_order_file_path
)
{
    using luyamlman::error::s_error;
    using luyamlman::error_details_types::s_allocation_failure;
    using luyamlman::error_details_types::s_filesystem_error;
    using luyamlman::error_details_types::s_load_order_read_error;

    result<std::vector<std::string>> parse_result{};
    bool                             error_occurred = false;
    std::set<std::string>            unique_plugins;
    std::ifstream load_order_file( a_load_order_file_path.data() );

    if( !load_order_file.is_open() )
    {
        parse_result = std::unexpected(
            s_error( s_filesystem_error{ a_load_order_file_path } )
        );

        return parse_result;
    }

    std::string line;
    uint32_t    line_number = 0;

    while( std::getline( load_order_file, line ) )
    {
        ++line_number;

        if( line.empty() || line[0] == '#' )
        {
            continue; // Skip empty lines and comments.
        }

        // Trim whitespace from the line.
        line.erase( 0, line.find_first_not_of( " \t" ) );
        line.erase( line.find_last_not_of( " \t" ) + 1 );

        if( line.empty() )
        {
            continue;
        }

        // Check for duplicate plugins.
        if( unique_plugins.find( line ) != unique_plugins.end() )
        {
            if( !error_occurred )
            {
                error_occurred = true;
                parse_result
                    = std::unexpected( s_error( s_load_order_read_error{
                        .m_code
                        = s_load_order_read_error::e_code::duplicate_plugin,
                        .m_line_number = line_number,
                        .m_plugin_name = line
                    } ) );
            }
            else
            {
                parse_result.error().insert_additional_error(
                    s_error( s_load_order_read_error{
                        .m_code
                        = s_load_order_read_error::e_code::duplicate_plugin,
                        .m_line_number = line_number,
                        .m_plugin_name = line
                    } )
                );
            }
        }

        if( error_occurred )
        {
            // Move here since we're not inserting into the vector anymore.
            // But I still want to see what other errors occur.
            unique_plugins.insert( std::move( line ) );
            continue;
        }

        unique_plugins.insert( line );
        parse_result->push_back( std::move( line ) );
    }

    // Consolidate errors if any occurred.
    // Although it might not be necessary in this function.
    if( error_occurred )
    {
        parse_result.error().consolidate_errors();
    }

    return parse_result;
}

} // namespace luyamlman::manager
