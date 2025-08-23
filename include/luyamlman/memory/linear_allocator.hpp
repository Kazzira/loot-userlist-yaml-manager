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
#include <stdexcept>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/memory/arena_allocator.hpp"
#include "luyamlman/memory/singleton.hpp"

namespace luyamlman::memory {

enum class e_usage
{
    single,
    multiple
};

template <typename ATag = struct s_default, e_usage AUsage = e_usage::multiple>
struct linear_allocator
{
        template <typename T>
        class allocator
        {
            public:
                using value_type      = T;
                using size_type       = std::size_t;
                using pointer         = T*;
                using const_pointer   = const T*;
                using reference       = T&;
                using const_reference = const T&;
                using difference_type = std::ptrdiff_t;

            public:
                allocator() noexcept {}

            public:
                static void
                intitialize(
                    std::size_t a_size
                )
                {
                    if( m_start != nullptr )
                    {
                        throw std::runtime_error{
                            "Linear allocator already initialized."
                        };
                    }

                    m_start = static_cast<T*>(
                        memory::arena_allocator<>::singleton::get_instance()
                            .allocate( a_size * sizeof( T ) )
                    );
                    m_size = a_size * sizeof( T );
                    m_used = 0;
                }

                T*
                allocate(
                    std::size_t a_count
                )
                {
                    if constexpr( AUsage == e_usage::single )
                    {
                        if( m_used != 0 )
                        {
                            throw std::bad_alloc{};
                        }
                    }

                    const size_t alignment = alignof( T );
                    const size_t current_address
                        = reinterpret_cast<size_t>( m_start ) + m_used;
                    const size_t allocation_size = a_count * sizeof( T );
                    const size_t padding         = [&]()
                    {
                        if( current_address % alignment == 0 )
                        {
                            return size_t{ 0 };
                        }

                        return alignment - ( current_address % alignment );
                    }();

                    if( m_used + padding + allocation_size > m_size )
                    {
                        throw std::bad_alloc{};
                    }

                    T* allocated_memory  = m_start + m_used + padding;
                    m_used              += padding + allocation_size;
                    return allocated_memory;
                }

                void
                deallocate(
                    [[maybe_unused]] T*          a_ptr,
                    [[maybe_unused]] std::size_t a_count
                ) noexcept
                {
                    if constexpr( AUsage == e_usage::single )
                    {
                        m_used = 0;
                    }

                    // Otherwise no deallocation can be done as
                    // there are many elements allocated.
                }

                static size_t
                size() noexcept
                {
                    return m_size;
                }

                static size_t
                used() noexcept
                {
                    return m_used;
                }

                static void
                reset_used() noexcept
                {
                    m_used = 0;
                }

                static void
                reset_allocator() noexcept
                {
                    m_start = nullptr;
                    m_size  = 0;
                    m_used  = 0;
                }

            private:
                inline static T*          m_start{ nullptr };
                inline static std::size_t m_size{ 0 };
                inline static std::size_t m_used{ 0 };
        };
};

} // namespace luyamlman::memory
