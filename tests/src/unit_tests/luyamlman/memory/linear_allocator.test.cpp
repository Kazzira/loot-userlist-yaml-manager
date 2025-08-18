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

template <typename T>
using str_allocator
    = luyamlman::memory::linear_allocator<T, struct s_string_allocator_tag>;

constexpr size_t k_string_vector_size       = 128;
constexpr size_t k_character_allocator_size = 21 * 128;

TEST_CASE(
    "luyamlman::memory::linear_allocator: Test vector and std::string.",
)
{
    using fast_string
        = std::basic_string<char, std::char_traits<char>, str_allocator<char>>;
    using str_vector = std::vector<fast_string, str_allocator<fast_string>>;

    luyamlman::memory::arena_allocator::get_instance(
        k_string_vector_size * sizeof( std::string )
        + k_character_allocator_size
    );
    str_allocator<fast_string>::intitialize( k_string_vector_size );
    str_allocator<char>::intitialize( k_character_allocator_size );

    str_vector vec;
    vec.reserve( 128 );

    CHECK( str_allocator<fast_string>::used() == sizeof( fast_string ) * 128 );
    CHECK( str_allocator<char>::used() == 0 );

    CHECK( str_allocator<char>::size() == 2688 );

    for( size_t i = 0; i < 128; ++i )
    {
        vec.emplace_back( "TWENTY TWENTY TWENTY" );
        CHECK( str_allocator<char>::used() == 21 * ( i + 1 ) );
    }
}
