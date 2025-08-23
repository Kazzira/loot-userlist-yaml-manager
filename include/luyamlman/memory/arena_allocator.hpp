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
#include <cstddef>
#include <optional>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/memory/singleton.hpp"
#include "luyamlman/tags.hpp"

namespace luyamlman::memory {

template <typename ATag = luyamlman::tags::s_default>
class arena_allocator
{
    public:
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type      = std::byte;
        using pointer         = std::byte*;
        using singleton = luyamlman::memory::singleton<arena_allocator<ATag>>;

    public:
        inline arena_allocator() = default;
        inline arena_allocator( size_t a_arena_size );

    public:
        inline ~arena_allocator() noexcept;

        // Deleting moves and copies because this is just
        // memory.

        inline arena_allocator( const arena_allocator& ) = delete;

        inline arena_allocator( arena_allocator&& )      = delete;

        inline arena_allocator&
        operator=( const arena_allocator& )
            = delete;

        inline arena_allocator&
        operator=( arena_allocator&& )
            = delete;

    public:
        inline void*
        allocate( size_t a_size );

        inline void
        reset() noexcept;

        size_t
        arena_used() const noexcept;

        size_t
        arena_size() const noexcept;

    private:
        std::byte* m_arena_start{ nullptr };
        size_t     m_arena_size{ 0 };
        size_t     m_arena_used{ 0 };
};
} // namespace luyamlman::memory

#include "luyamlman/memory/arena_allocator.inl"
