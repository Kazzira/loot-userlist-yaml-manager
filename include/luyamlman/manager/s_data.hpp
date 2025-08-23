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
#include <memory>
#include <span>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/concepts/c_string_view_strong_type.hpp"
#include "luyamlman/error/s_error.hpp"
#include "luyamlman/types/t_loot_group_name.hpp"
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
class s_data
{
    private:
        using t_load_order_plugin_vector = std::vector<
            luyamlman::types::t_plugin_name,
            ALoadOrderPluginVectorAllocator<luyamlman::types::t_plugin_name>>;

        using t_load_order_history_plugin_vector = std::vector<
            luyamlman::types::t_plugin_name,
            ALoadOrderHistoryPluginVectorAllocator<
                luyamlman::types::t_plugin_name>>;

    public:
        inline s_data() = default;

        inline ~s_data() noexcept;

        inline s_data( const s_data& ) = default;

        inline s_data( s_data&& )      = default;

        inline s_data&
        operator=( const s_data& )
            = default;

        inline s_data&
        operator=( s_data&& )
            = default;

    public:
        result<void>
        parse_load_order_file( std::string_view a_load_order_file_path );

        result<void>
        parse_load_order_history_file( std::string_view a_load_order_file_path
        );

    public:
        inline std::span<luyamlman::types::t_plugin_name>
        load_order() noexcept
        {
            return m_load_order;
        }

        inline std::span<const luyamlman::types::t_plugin_name>
        load_order() const noexcept
        {
            return m_load_order;
        }

        inline std::span<luyamlman::types::t_plugin_name>
        load_order_history() noexcept
        {
            return m_load_order_history;
        }

        inline std::span<const luyamlman::types::t_plugin_name>
        load_order_history() const noexcept
        {
            return m_load_order_history;
        }

    private:
        template <concepts::c_string_view_strong_type AStringViewStrongType>
        void
        deallocate_strings_using_std_allocator(
            std::span<AStringViewStrongType> a_strings
        ) noexcept;

    private:
        t_load_order_plugin_vector         m_load_order{ 0 };
        t_load_order_history_plugin_vector m_load_order_history{ 0 };
};

} // namespace luyamlman::manager

#include "luyamlman/manager/s_data.inl"
