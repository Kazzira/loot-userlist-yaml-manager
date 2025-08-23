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

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/s_error.hpp"
#include "luyamlman/manager/load_order_parser.hpp"
#include "luyamlman/manager/s_manager.hpp"

template <
    template <class> typename ALoadOrderPluginVectorAllocator,
    template <class> typename ALoadOrderHistoryPluginVectorAllocator,

    template <class> typename ALoadOrderPluginStringAllocator,
    template <class> typename ALoadOrderHistoryPluginStringAllocator,

    template <class> typename ASingleUseStringAllocator>
luyamlman::result<luyamlman::manager::s_manager<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>>
luyamlman::manager::s_manager<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>::
    create(
        std::string_view a_load_order_file_path,
        std::string_view a_config_json_file_path
    )
{
    using luyamlman::error::s_error;

    s_manager mgr{};

    auto      init_result
        = mgr.initialize( a_load_order_file_path, a_config_json_file_path );

    if( !init_result )
    {
        return std::unexpected( std::move( init_result.error() ) );
    }

    return mgr;
}

template <
    template <class> typename ALoadOrderPluginVectorAllocator,
    template <class> typename ALoadOrderHistoryPluginVectorAllocator,

    template <class> typename ALoadOrderPluginStringAllocator,
    template <class> typename ALoadOrderHistoryPluginStringAllocator,

    template <class> typename ASingleUseStringAllocator>
luyamlman::result<luyamlman::manager::s_manager<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>*>
luyamlman::manager::s_manager<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>::
    create_ptr(
        std::string_view a_load_order_file_path,
        std::string_view a_config_json_file_path
    )
{
    using luyamlman::error::s_error;
    using luyamlman::error_details_types::s_allocation_failure;

    s_manager* mgr = nullptr;

    try
    {
        mgr = new s_manager();
    }
    catch( const std::bad_alloc& )
    {
        return std::unexpected( s_error( s_allocation_failure{} ) );
    }

    auto init_result
        = mgr->initialize( a_load_order_file_path, a_config_json_file_path );

    if( !init_result )
    {
        delete mgr;
        return std::unexpected( std::move( init_result.error() ) );
    }

    return mgr;
}

template <
    template <class> typename ALoadOrderPluginVectorAllocator,
    template <class> typename ALoadOrderHistoryPluginVectorAllocator,

    template <class> typename ALoadOrderPluginStringAllocator,
    template <class> typename ALoadOrderHistoryPluginStringAllocator,

    template <class> typename ASingleUseStringAllocator>
luyamlman::result<void>
luyamlman::manager::s_manager<
    ALoadOrderPluginVectorAllocator,
    ALoadOrderHistoryPluginVectorAllocator,
    ALoadOrderPluginStringAllocator,
    ALoadOrderHistoryPluginStringAllocator,
    ASingleUseStringAllocator>::
    initialize(
        std::string_view                  a_load_order_file_path,
        [[maybe_unused]] std::string_view a_config_json_file_path
    )
{
    using luyamlman::error::s_error;
    using luyamlman::manager::parse_load_order_file;

    auto load_order_result
        = m_data.parse_load_order_file( a_load_order_file_path );

    if( !load_order_result )
    {
        return std::unexpected( std::move( load_order_result.error() ) );
    }

    return {};
}
