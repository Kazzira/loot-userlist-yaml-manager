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
#include <string_view>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/s_error.hpp"
#include "luyamlman/manager/s_data.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

namespace luyamlman::manager {

template <
    template <class> typename ALoadOrderPluginVectorAllocator = std::allocator,
    template <class> typename ALoadOrderHistoryPluginVectorAllocator
    = std::allocator,
    template <class> typename ALoadOrderPluginStringAllocator = std::allocator,
    template <class> typename ALoadOrderHistoryPluginStringAllocator
    = std::allocator,

    template <class> typename ASingleUseStringAllocator = std::allocator>
class s_manager
{
    private:
        s_manager() noexcept = default;

    public:
        static result<s_manager>
        create(
            std::string_view a_load_order_file_path,
            std::string_view a_config_json_file_path
        );

        static result<s_manager *>
        create_ptr(
            std::string_view a_load_order_file_path,
            std::string_view a_config_json_file_path
        );

    private:
        result<void>
        initialize(
            std::string_view a_load_order_file_path,
            std::string_view a_config_json_file_path
        );

    private:
        luyamlman::manager::s_data<
            ALoadOrderPluginVectorAllocator,
            ALoadOrderHistoryPluginVectorAllocator,
            ALoadOrderPluginStringAllocator,
            ALoadOrderHistoryPluginStringAllocator>
            m_data;
};

} // namespace luyamlman::manager

#include "luyamlman/manager/s_manager.tpp"
