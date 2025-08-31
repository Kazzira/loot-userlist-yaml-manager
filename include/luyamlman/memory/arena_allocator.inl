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
#include <new>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/memory/arena_allocator.hpp"

template <typename ATag>
luyamlman::memory::arena_allocator<ATag>::arena_allocator(
    size_t a_arena_size
)
{
    m_arena_start = new std::byte[a_arena_size];
    m_arena_size  = a_arena_size;
    m_arena_used  = 0;
}

template <typename ATag>
luyamlman::memory::arena_allocator<ATag>::~arena_allocator() noexcept
{
    delete[] m_arena_start;
}

template <typename ATag>
void*
luyamlman::memory::arena_allocator<ATag>::allocate(
    size_t a_size
)
{
    const size_t alignment = alignof( std::byte );
    const size_t current_address
        = reinterpret_cast<size_t>( m_arena_start ) + m_arena_used;
    const size_t padding = [&]() -> size_t
    {
        if( current_address % alignment == 0 )
        {
            return 0;
        }

        return alignment - ( current_address % alignment );
    }();

    if( m_arena_used + a_size + padding > m_arena_size )
    {
        throw luyamlman::error::alloc_fail(
            "luyamlman::memory::arena_allocator<ATag>::allocate: Failed to "
            "allocate memory from arena. Requested size: "
            + std::to_string( a_size )
            + " bytes. Arena size: "
            + std::to_string( m_arena_size )
            + " bytes. Arena used: "
            + std::to_string( m_arena_used )
            + " bytes."
        );
    }

    void* allocated_memory  = m_arena_start + m_arena_used + padding;
    m_arena_used           += a_size + padding;
    return allocated_memory;
}

template <typename ATag>
void
luyamlman::memory::arena_allocator<ATag>::reset() noexcept
{
    m_arena_used = 0;
}

template <typename ATag>
size_t
luyamlman::memory::arena_allocator<ATag>::arena_used() const noexcept
{
    return m_arena_used;
}

template <typename ATag>
size_t
luyamlman::memory::arena_allocator<ATag>::arena_size() const noexcept
{
    return m_arena_size;
}
