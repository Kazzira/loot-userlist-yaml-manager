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
/////////////////////////////////////////////////////////////////////////////
// STANDARD LIBRARY INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include <optional>
#include <string>
#include <string_view>

//////////////////////////////////////////////////////////////////////////////
// FFI INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "loot_userlist_yaml_manager_ffi.h"

namespace luyamlman_tests::ffi {

class s_ffi_wrapper
{
    public:
        s_ffi_wrapper(
            const std::string_view load_order_file_path,
            const std::string_view config_path
        );

    public:
        ~s_ffi_wrapper() noexcept;

    public:
        s_ffi_wrapper( s_ffi_wrapper&& ) noexcept;
        s_ffi_wrapper( const s_ffi_wrapper& ) noexcept = delete;
        s_ffi_wrapper&
        operator=( s_ffi_wrapper&& ) noexcept;
        s_ffi_wrapper&
        operator=( const s_ffi_wrapper& ) noexcept
            = delete;

    public:
        operator bool() const noexcept { return m_handle != nullptr; }

    public:
        uint32_t
        construction_return_code() const noexcept
        {
            return m_construction_return_code;
        }

        std::optional<std::string>&
        error_json_contents() noexcept
        {
            return m_error_json_contents;
        }

        const std::optional<std::string>&
        error_json_contents() const noexcept
        {
            return m_error_json_contents;
        }

    private:
        uint32_t                          m_construction_return_code;
        std::optional<std::string>        m_error_json_contents{ std::nullopt };
        loot_userlist_yaml_manager_handle m_handle{ nullptr };
};

} // namespace luyamlman_tests::ffi
