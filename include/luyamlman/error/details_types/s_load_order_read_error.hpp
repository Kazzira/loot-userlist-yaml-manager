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
#include <cstdint>

//////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <meta_enum.hpp>
#include <nlohmann/json.hpp>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/types/t_plugin_name.hpp"

namespace luyamlman::error_details_types {

struct s_load_order_read_error
{
        meta_enum_class( e_code, uint32_t, duplicate_plugin ) using error_code
            = e_code;

        error_code                      m_code;
        uint32_t                        m_line_number;
        luyamlman::types::t_plugin_name m_plugin_name;
};

NLOHMANN_JSON_SERIALIZE_ENUM(
    s_load_order_read_error::e_code,
    {
        { s_load_order_read_error::e_code::duplicate_plugin, "duplicate_plugin"
        }
}
)

} // namespace luyamlman::error_details_types
