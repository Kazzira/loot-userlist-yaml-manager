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
/////////////////////////////////////////////////////////////////////////////
// TESTS INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include "luyamlman_tests/ffi/ffi_wrapper.hpp"

namespace luyamlman_tests::ffi {

s_ffi_wrapper::s_ffi_wrapper(
    const std::string_view load_order_file_path,
    const std::string_view config_path
)
{
    char* error_json_contents_ptr = nullptr;

    m_construction_return_code    = loot_userlist_yaml_manager_create_handle(
        &m_handle,
        load_order_file_path.data(),
        config_path.data(),
        &error_json_contents_ptr
    );

    if( !m_handle && error_json_contents_ptr )
    {
        m_error_json_contents.emplace( error_json_contents_ptr );
        loot_userlist_yaml_manager_destroy_string( error_json_contents_ptr );
    }
}

s_ffi_wrapper::~s_ffi_wrapper() noexcept
{
    loot_userlist_yaml_manager_destroy_handle( m_handle );
}

s_ffi_wrapper::s_ffi_wrapper(
    s_ffi_wrapper&& other
) noexcept
    : m_handle( other.m_handle )
{
    other.m_handle
        = nullptr; // Ensure the moved-from object does not destroy the handle.
}

s_ffi_wrapper&
s_ffi_wrapper::operator=(
    s_ffi_wrapper&& other
) noexcept
{
    if( this != &other )
    {
        loot_userlist_yaml_manager_destroy_handle( m_handle );
        m_handle       = other.m_handle;
        other.m_handle = nullptr;
    }

    return *this;
}

} // namespace luyamlman_tests::ffi
