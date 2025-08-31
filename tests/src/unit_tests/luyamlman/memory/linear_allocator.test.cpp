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
#include <string>
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <catch2/catch_all.hpp>

/////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include "luyamlman/memory/arena_allocator.hpp"
#include "luyamlman/memory/linear_allocator.hpp"
#include "luyamlman/raii/s_scoped_global_allocator_handler.hpp"
#include "luyamlman/tags.hpp"

template <typename T>
using str_allocator = luyamlman::memory::linear_allocator<
    luyamlman::tags::s_default,
    luyamlman::tags::s_test_01,
    luyamlman::memory::e_usage::multiple>::allocator<T>;

#ifdef _WIN32
constexpr size_t k_str_size = 32;
#else
constexpr size_t k_str_size = 21;
#endif

constexpr size_t k_string_vector_size       = 128;

#ifdef _WIN32
#ifdef NODEBUG
constexpr size_t k_character_allocator_size = k_str_size * 128;
#else
constexpr size_t k_character_allocator_size = 16 * 256;
#endif
#else
constexpr size_t k_character_allocator_size = k_str_size * 128;
#endif

using fast_string
    = std::basic_string<char, std::char_traits<char>, str_allocator<char>>;
using str_vector = std::vector<fast_string, str_allocator<fast_string>>;

class s_str_allocator_handler
    : public luyamlman::raii::s_scoped_global_allocator_handler
{
    public:
        s_str_allocator_handler(
            size_t a_arena_size = k_string_vector_size * sizeof( std::string )
                                + k_character_allocator_size + k_str_size * 128,
                                [[maybe_unused]]
            size_t a_str_allocator_char_size   = k_character_allocator_size,
            size_t a_str_allocator_string_size = k_string_vector_size
        )
        {
            luyamlman::memory::arena_allocator<>::singleton::get_instance(
                a_arena_size
            );
            str_allocator<fast_string>::intitialize( a_str_allocator_string_size
            );
#ifdef _WIN32
#ifdef NODEBUG
            str_allocator<char>::intitialize( a_str_allocator_char_size );
#else
            str_allocator<std::_Container_proxy>::intitialize( k_string_vector_size * 2 );
            str_allocator<char>::intitialize( k_str_size * 128 );
#endif
#else
            str_allocator<char>::intitialize( a_str_allocator_char_size );
#endif
        }

        ~s_str_allocator_handler()
        {
            str_allocator<fast_string>::reset_allocator();
            str_allocator<char>::reset_allocator();
            luyamlman::memory::arena_allocator<>::singleton::reset_instance();
        }
};

TEST_CASE(
    "luyamlman::memory::linear_allocator: Test vector and std::string.",
)
{
    const s_str_allocator_handler handler;

    str_vector                    vec;
    vec.reserve( 128 );

    CHECK( str_allocator<fast_string>::used() == sizeof( fast_string ) * 128 );
    CHECK( str_allocator<char>::used() == 0 );

    CHECK( str_allocator<char>::size() == k_str_size * 128 );

    for( size_t i = 0; i < 128; ++i )
    {
        vec.emplace_back( "TWENTY TWENTY TWENTY" );
        CHECK( str_allocator<char>::used() == k_str_size * ( i + 1 ) );
    }
}
