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
#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////
// FFI INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "loot_userlist_yaml_manager_ffi.h"

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/manager/load_order_parser.hpp"

namespace {

class s_loot_userlist_yaml_manager_handle
{
    public:
        std::vector<std::string> m_load_order;
};

} // namespace

uint32_t
LUYAMLMAN_OK()
{
    return 1;
}

uint32_t
LUYAMLMAN_ERR_ALLOCATION_FAILED()
{
    return 2;
}

// Errors that can occur when creating the handle.

uint32_t
LUYAMLMAN_ERR_LOAD_ORDER_FILE_NOT_FOUND()
{
    return 3;
}

uint32_t
LUYAMLMAN_ERR_LOAD_ORDER_FILE_INVALID()
{
    return 4;
}

uint32_t
LUYAMLMAN_ERR_CONFIG_JSON_FILE_NOT_FOUND()
{
    return 5;
}

uint32_t
LUYAMLMAN_ERR_CONFIG_JSON_FILE_INVALID()
{
    return 6;
}

uint32_t
LUYAMLMAN_ERR_USERLIST_ERROR_JSON_INCLUDED()
{
    return 7;
}

uint32_t
loot_userlist_yaml_manager_create_handle(
    [[maybe_unused]] loot_userlist_yaml_manager_handle* a_handle,
    [[maybe_unused]] const char*                        a_load_order_file_path,
    [[maybe_unused]] const char*                        a_config_json_file_path,
    [[maybe_unused]] char** a_userlist_error_json_contents
)
{
    try
    {
        auto load_order
            = luyamlman::manager::parse_load_order_file( a_load_order_file_path
            );

        if( !load_order )
        {
            return LUYAMLMAN_ERR_LOAD_ORDER_FILE_NOT_FOUND();
        }

        *a_handle = new s_loot_userlist_yaml_manager_handle();

        static_cast<s_loot_userlist_yaml_manager_handle*>( *a_handle )
            ->m_load_order
            = std::move( *load_order );
    }
    catch( const std::bad_alloc& )
    {
        return LUYAMLMAN_ERR_ALLOCATION_FAILED();
    }

    return LUYAMLMAN_OK();
}

void
loot_userlist_yaml_manager_destroy_handle(
    loot_userlist_yaml_manager_handle a_handle
)
{
    delete static_cast<s_loot_userlist_yaml_manager_handle*>( a_handle );
}

void
loot_userlist_yaml_manager_destroy_error_json_contents(
    [[maybe_unused]] char* a_error_json_contents
)
{
    delete[] a_error_json_contents;
}
