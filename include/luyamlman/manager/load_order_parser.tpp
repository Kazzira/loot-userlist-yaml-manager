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
#include <cstring>
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
#include "luyamlman/manager/load_order_parser.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

template <
    template <class> typename AVectorAllocator,
    template <class> typename ACharAllocator,
    template <class> typename ATempStringCharAllocator>
luyamlman::result<std::vector<
    luyamlman::types::t_plugin_name,
    AVectorAllocator<luyamlman::types::t_plugin_name>>>
luyamlman::manager::parse_load_order_file(
    std::string_view a_load_order_file_path
)
{
    enum class e_action
    {
        run,
        dry_run
    };

    using luyamlman::result;
    using luyamlman::error::s_error;
    using luyamlman::error_details_types::s_allocation_failure;
    using luyamlman::error_details_types::s_filesystem_error;
    using luyamlman::error_details_types::s_load_order_read_error;
    using luyamlman::types::t_plugin_name;

    std::vector<t_plugin_name, AVectorAllocator<t_plugin_name>> parse_vector{};

    result<std::vector<t_plugin_name, AVectorAllocator<t_plugin_name>>>
                            parse_result{};

    bool                    error_occurred = false;
    std::set<t_plugin_name> unique_plugins;
    std::ifstream           load_order_file( a_load_order_file_path.data() );

    // Manager-2
    if( !load_order_file.is_open() )
    {
        parse_result = std::unexpected(
            s_error( s_filesystem_error{ a_load_order_file_path } )
        );

        return parse_result;
    }

    std::basic_string<
        char,
        std::char_traits<char>,
        ATempStringCharAllocator<char>>
         line;

    auto do_run = [&]<e_action action>() -> uint32_t
    {
        uint32_t line_number = 0;

        while( std::getline( load_order_file, line ) )
        {
            ++line_number;

            if( line.empty() || line[0] == '#' )
            {
                if constexpr( action == e_action::dry_run )
                {
                    --line_number;
                }

                continue; // Skip empty lines and comments.
            }

            // Trim whitespace from the line.
            line.erase( 0, line.find_first_not_of( " \t" ) );
            line.erase( line.find_last_not_of( " \t" ) + 1 );

            if( line.empty() )
            {
                if constexpr( action == e_action::dry_run )
                {
                    --line_number;
                }

                continue;
            }

            if constexpr( action == e_action::dry_run )
            {
                continue;
            }

            // ALLOCATION TIME
            ACharAllocator<char> allocator;
            char* plugin_cstr_without_null = allocator.allocate( line.size() );
            (void
            )std::memcpy( plugin_cstr_without_null, line.data(), line.size() );

            t_plugin_name plugin_name{
                plugin_cstr_without_null,
                line.size(),
            };

            // Manager-2
            // Manager-3
            if( unique_plugins.find( plugin_name ) != unique_plugins.end() )
            {
                if( !error_occurred )
                {
                    error_occurred = true;
                    parse_result
                        = std::unexpected( s_error( s_load_order_read_error{
                            .m_code
                            = s_load_order_read_error::e_code::duplicate_plugin,
                            .m_line_number = line_number,
                            .m_plugin_name = plugin_name
                        } ) );
                }
                else
                {
                    parse_result.error().insert_additional_error(
                        s_error( s_load_order_read_error{
                            .m_code
                            = s_load_order_read_error::e_code::duplicate_plugin,
                            .m_line_number = line_number,
                            .m_plugin_name = plugin_name
                        } )
                    );
                }
            }

            unique_plugins.insert( plugin_name );
            parse_vector.push_back( plugin_name );
        }

        return line_number;
    };

    auto number_of_lines = do_run.template operator()<e_action::dry_run>();

    if( number_of_lines == 0 )
    {
        return parse_result;
    }

    parse_vector.reserve( number_of_lines );
    load_order_file.clear();
    load_order_file.seekg( 0 );
    (void)do_run.template operator()<e_action::run>();

    if( error_occurred )
    {
        parse_result.error().consolidate_errors();

        // Place the vector here so that whoever owns this
        // can deallocate the strings in the vector, if necessary.
        parse_result.error().return_value( std::move( parse_vector ) );
    }
    else
    {
        parse_result = std::move( parse_vector );
    }

    return parse_result;
}
