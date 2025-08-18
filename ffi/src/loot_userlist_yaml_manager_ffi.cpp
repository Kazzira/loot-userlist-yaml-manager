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
#include "luyamlman/error/details_types/s_allocation_failure.hpp"
#include "luyamlman/manager/s_manager.hpp"
#include "luyamlman/overloads.hpp"

namespace {

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
    using luyamlman::error_details_types::s_allocation_failure;
    using luyamlman::error_details_types::s_filesystem_error;
    using luyamlman::error_details_types::s_load_order_read_error;
    try
    {
        auto mgr = luyamlman::manager::s_manager::
            create_ptr( a_load_order_file_path, a_config_json_file_path );

        if( !mgr )
        {
            return std::visit(
                luyamlman::overloads{
                    []( const s_allocation_failure& )
                    {
                        return LUYAMLMAN_ERR_ALLOCATION_FAILED();
                    },
                    [&]( const s_filesystem_error& fs_err )
                    {
                        if( fs_err.m_path == a_load_order_file_path )
                        {
                            return LUYAMLMAN_ERR_LOAD_ORDER_FILE_NOT_FOUND();
                        }
                        else if( fs_err.m_path == a_config_json_file_path )
                        {
                            return LUYAMLMAN_ERR_CONFIG_JSON_FILE_NOT_FOUND();
                        }
                        else
                        {
                            return LUYAMLMAN_ERR_ALLOCATION_FAILED();
                        }
                    },
                    []( const s_load_order_read_error& )
                    {
                        return LUYAMLMAN_ERR_LOAD_ORDER_FILE_INVALID();
                    }
                },
                mgr.error().details()
            );
        }

        *a_handle = *mgr;

        return LUYAMLMAN_OK();
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
    delete static_cast<luyamlman::manager::s_manager*>( a_handle );
}

void
loot_userlist_yaml_manager_destroy_string(
    char* a_str
)
{
    delete[] a_str;
}
