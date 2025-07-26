/*
Copyright (C) 2024-2025 Zachary Dakota Meyer. All rights reserved.

This file is part of the LOOT Userlist.yaml Manager project.

LOOT Userlist.yaml Manager is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

LOOT Userlist.yaml Manager is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LOOT Userlist.yaml Manager.  If not, see <http://www.gnu.org/licenses/>.
*/
//PAGE: Includes ------------------------------------------------------------/
//////////////////////////////////////////////////////////////////////////////
// STANDARD LIBRARY INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////
// FFI INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "loot_userlist_yaml_manager_ffi.h"


//PAGE: Return Codes --------------------------------------------------------/
const uint32_t LUYAMLMAN_OK = 1;

const uint32_t LUYAMLMAN_ERR_ALLOCATION_FAILED = 2;

const uint32_t LUYAMLMAN_ERR_LOAD_ORDER_FILE_NOT_FOUND = 3;
const uint32_t LUYAMLMAN_ERR_LOAD_ORDER_FILE_INVALID = 4;
const uint32_t LUYAMLMAN_ERR_CONFIG_JSON_FILE_NOT_FOUND = 5;
const uint32_t LUYAMLMAN_ERR_CONFIG_JSON_FILE_INVALID = 6;
const uint32_t LUYAMLMAN_ERR_USERLIST_ERROR_JSON_INCLUDED = 7;

//PAGE: loot_userlist_yaml_manager_create_handle ----------------------------/
uint32_t
loot_userlist_yaml_manager_create_handle(
    [[maybe_unused]]
    loot_userlist_yaml_manager_handle* a_handle,
    [[maybe_unused]]
    const char*                        a_load_order_file_path,
    [[maybe_unused]]
    const char*                        a_config_json_file_path,
    [[maybe_unused]]
    char**                             a_userlist_error_json_contents
)
{
    return LUYAMLMAN_OK;
}

//PAGE: loot_userlist_yaml_manager_destroy_handle ---------------------------/
void
loot_userlist_yaml_manager_destroy_handle(
    [[maybe_unused]]
    loot_userlist_yaml_manager_handle handle
)
{

}

//PAGE: loot_userlist_yaml_manager_destroy_error_json_contents --------------/
void
loot_userlist_yaml_manager_destroy_error_json_contents(
    [[maybe_unused]]
    char* error_json_contents
)
{
}


//PAGE: EOF -----------------------------------------------------------------/