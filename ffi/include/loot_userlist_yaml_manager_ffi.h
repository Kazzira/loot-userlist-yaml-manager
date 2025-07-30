#ifndef __LOOT_USERLIST_YAML_MANAGER_FFI_H__
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
#define __LOOT_USERLIST_YAML_MANAGER_FFI_H__

//////////////////////////////////////////////////////////////////////////////
// STANDARD LIBRARY INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef void* loot_userlist_yaml_manager_handle;

    uint32_t
    LUYAMLMAN_OK();

    uint32_t
    LUYAMLMAN_ERR_ALLOCATION_FAILED();

    uint32_t
    LUYAMLMAN_ERR_LOAD_ORDER_FILE_NOT_FOUND();
    uint32_t
    LUYAMLMAN_ERR_LOAD_ORDER_FILE_INVALID();
    uint32_t
    LUYAMLMAN_ERR_CONFIG_JSON_FILE_NOT_FOUND();
    uint32_t
    LUYAMLMAN_ERR_CONFIG_JSON_FILE_INVALID();
    uint32_t
    LUYAMLMAN_ERR_USERLIST_ERROR_JSON_INCLUDED();

    uint32_t
    loot_userlist_yaml_manager_create_handle(
        loot_userlist_yaml_manager_handle* a_handle,
        const char*                        a_load_order_file_path,
        const char*                        a_config_json_file_path,
        char**                             a_userlist_error_json_contents
    );

    void
    loot_userlist_yaml_manager_destroy_handle(
        loot_userlist_yaml_manager_handle a_handle
    );

    void
    loot_userlist_yaml_manager_destroy_string( char* a_str );

#ifdef __cplusplus
}
#endif

#endif // __LOOT_USERLIST_YAML_MANAGER_FFI_H__
