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
#include <type_traits>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/manager/load_order_parser.hpp"
#include "luyamlman/manager/s_data.hpp"
#include "luyamlman/types/t_plugin_name.hpp"
#include "luyamlman/unit.hpp"

template <
    template <class> typename ALoadOrderPluginVectorAllocator,
    template <class> typename ALoadOrderHistoryPluginVectorAllocator,

    template <class> typename ALoadOrderPluginStringAllocator,
    template <class> typename ALoadOrderHistoryPluginStringAllocator,
    template <class> typename ASingleUseStringAllocator>
luyamlman::manager::s_data<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>::~s_data() noexcept
{
    // Load Order Vector.
    if constexpr( std::is_same_v<
                      ALoadOrderPluginStringAllocator<char>,
                      std::allocator<char>> )
    {
        deallocate_strings_using_std_allocator<luyamlman::types::t_plugin_name>(
            m_load_order
        );
    }

    // Load Order History Vector.
    if constexpr( std::is_same_v<
                      ALoadOrderHistoryPluginStringAllocator<char>,
                      std::allocator<char>> )
    {
        deallocate_strings_using_std_allocator<luyamlman::types::t_plugin_name>(
            m_load_order_history
        );
    }
}

template <
    template <class> typename ALoadOrderPluginVectorAllocator,
    template <class> typename ALoadOrderHistoryPluginVectorAllocator,

    template <class> typename ALoadOrderPluginStringAllocator,
    template <class> typename ALoadOrderHistoryPluginStringAllocator,

    template <class> typename ASingleUseStringAllocator>
template <luyamlman::concepts::c_string_view_strong_type AStringViewStrongType>
void
luyamlman::manager::s_data<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>::
    deallocate_strings_using_std_allocator(
        std::span<AStringViewStrongType> a_strings
    ) noexcept
{
    for( auto& str : a_strings )
    {
        std::allocator<char> alloc;

        alloc.deallocate(
            const_cast<char*>( str.value_of().data() ),
            str.value_of().size()
        );
    }
}

template <
    template <class> typename ALoadOrderPluginVectorAllocator,
    template <class> typename ALoadOrderHistoryPluginVectorAllocator,

    template <class> typename ALoadOrderPluginStringAllocator,
    template <class> typename ALoadOrderHistoryPluginStringAllocator,

    template <class> typename ASingleUseStringAllocator>
luyamlman::result<void>
luyamlman::manager::s_data<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>::
    parse_load_order_file(
        std::string_view a_load_order_file_path
    )
{
    return luyamlman::manager::parse_load_order_file<
               ALoadOrderPluginVectorAllocator,
               ALoadOrderPluginStringAllocator,
               ASingleUseStringAllocator>( a_load_order_file_path )
        .transform(
            [this]( auto a_load_order ) -> void
            {
                m_load_order = std::move( a_load_order );
            }
        )
        .or_else(
            [this]( luyamlman::error::s_error a_error
            ) -> luyamlman::result<void>
            {
                a_error.return_value_as<t_load_order_plugin_vector>().and_then(
                    [this]( auto a_load_order )
                    {
                        m_load_order = std::move( a_load_order );
                        return std::make_optional( unit );
                    }
                );

                return std::unexpected( std::move( a_error ) );
            }
        );
}

template <
    template <class> typename ALoadOrderPluginVectorAllocator,
    template <class> typename ALoadOrderHistoryPluginVectorAllocator,

    template <class> typename ALoadOrderPluginStringAllocator,
    template <class> typename ALoadOrderHistoryPluginStringAllocator,

    template <class> typename ASingleUseStringAllocator>
luyamlman::result<void>
luyamlman::manager::s_data<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>::
    parse_load_order_history_file(
        std::string_view a_load_order_file_path
    )
{
    return luyamlman::manager::parse_load_order_file<
               ALoadOrderHistoryPluginVectorAllocator,
               ALoadOrderHistoryPluginStringAllocator,
               ASingleUseStringAllocator>( a_load_order_file_path )
        .transform(
            [this]( auto a_load_order ) -> void
            {
                m_load_order_history = std::move( a_load_order );
            }
        )
        .or_else(
            [this]( luyamlman::error::s_error a_error )
            {
                a_error.return_value_as<t_load_order_history_plugin_vector>()
                    .and_then(
                        [this]( auto a_load_order )
                        {
                            m_load_order_history = std::move( a_load_order );
                            return std::make_optional( unit );
                        }
                    );

                return std::unexpected( std::move( a_error ) );
            }
        );
}
