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
#include <string_view>

//////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <strong_type/formattable.hpp>
#include <strong_type/hashable.hpp>
#include <strong_type/indexed.hpp>
#include <strong_type/iostreamable.hpp>
#include <strong_type/ordered.hpp>
#include <strong_type/strong_type.hpp>

namespace luyamlman::types {

using t_loot_group_name = strong::type<
    std::string_view,
    struct s_loot_group_name_tag,
    strong::formattable,
    strong::hashable,
    strong::indexed<>,
    strong::ostreamable,
    strong::ordered,
    strong::partially_ordered>;

} // namespace luyamlman::types

namespace luyamlman::literals {

inline constexpr luyamlman::types::t_loot_group_name
operator"" _loot_group(
    const char* a_loot_group_name,
    size_t      a_length
) noexcept
{
    return luyamlman::types::t_loot_group_name{
        std::string_view{ a_loot_group_name, a_length }
    };
}

} // namespace luyamlman::literals

#ifdef LUYALMMAN_INSTANTIATE_TEMPLATES_TYPES_TLOOTGROUPNAME
template struct strong::indexed<>;
template class strong::type<
    std::string_view,
    struct s_loot_group_name_tag,
    strong::formattable,
    strong::hashable,
    strong::indexed<>,
    strong::ostreamable,
    strong::ordered,
    strong::partially_ordered>;

#else
extern template struct strong::indexed<>;
extern template class strong::type<
    std::string_view,
    struct s_loot_group_name_tag,
    strong::formattable,
    strong::hashable,
    strong::indexed<>,
    strong::ostreamable,
    strong::ordered,
    strong::partially_ordered>;
#endif
