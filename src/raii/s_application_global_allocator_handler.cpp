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
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/raii/s_application_global_allocator_handler.hpp"
#include "luyamlman/memory/arena_allocator.hpp"
#include "luyamlman/memory/linear_allocator.hpp"
#include "luyamlman/tags.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

luyamlman::raii::s_application_global_allocator_handler::
    ~s_application_global_allocator_handler() noexcept
{
    luyamlman::memory::linear_allocator<
        luyamlman::tags::s_default,
        luyamlman::tags::s_load_order_strings,
        memory::e_usage::multiple>::allocator<char>::reset_allocator();

    luyamlman::memory::linear_allocator<
        luyamlman::tags::s_default,
        tags::s_load_order_strings,
        memory::e_usage::single>::allocator<char>::reset_allocator();

    luyamlman::memory::linear_allocator<
        luyamlman::tags::s_default,
        luyamlman::tags::s_load_order_history_strings,
        memory::e_usage::multiple>::allocator<char>::reset_allocator();

    luyamlman::memory::linear_allocator<
        luyamlman::tags::s_default,
        luyamlman::tags::s_load_order_vector,
        memory::e_usage::multiple>::allocator<types::t_plugin_name>::
        reset_allocator();

    luyamlman::memory::linear_allocator<
        luyamlman::tags::s_default,
        luyamlman::tags::s_load_order_history_vector,
        memory::e_usage::multiple>::allocator<types::t_plugin_name>::
        reset_allocator();

    luyamlman::memory::arena_allocator<>::singleton::reset_instance();
}
