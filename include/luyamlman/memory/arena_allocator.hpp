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
#include <new>

namespace luyamlman::memory {
class arena_allocator
{
    public:
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type      = std::byte;
        using pointer         = std::byte*;

    public:
        static arena_allocator&
        get_instance(
            size_t a_arena_size = 32 * 1024 * 1024
        ) noexcept
        {
            static arena_allocator instance( a_arena_size );
            return instance;
        }

    private:
        arena_allocator(
            size_t a_arena_size
        ) noexcept
        {
            m_arena_start = new std::byte[a_arena_size];
            m_arena_size  = a_arena_size;
            m_arena_used  = 0;
        }

    public:
        void*
        allocate(
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
                throw std::bad_alloc{};
            }

            void* allocated_memory  = m_arena_start + m_arena_used + padding;
            m_arena_used           += a_size + padding;
            return allocated_memory;
        }

        void
        reset() noexcept
        {
            m_arena_used = 0;
        }

        size_t
        arena_used() const noexcept
        {
            return m_arena_used;
        }

        size_t
        arena_size() const noexcept
        {
            return m_arena_size;
        }

    private:
        std::byte* m_arena_start{ nullptr };
        size_t     m_arena_size{ 0 };
        size_t     m_arena_used{ 0 };
};
} // namespace luyamlman::memory
