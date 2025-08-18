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
/////////////////////////////////////////////////////////////////////////////
// STANDARD LIBRARY INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include <cstdint>

/////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include <strong_type/arithmetic.hpp>
#include <strong_type/ordered.hpp>
#include <strong_type/strong_type.hpp>

namespace benchmark::types {

using t_depth = strong::
    type<int32_t, struct t_depth_tag, strong::ordered, strong::arithmetic>;

namespace literals {
    inline constexpr t_depth
    operator"" _depth(
        unsigned long long value
    ) noexcept
    {
        return t_depth{ static_cast<int32_t>( value ) };
    }
} // namespace literals
} // namespace benchmark::types
