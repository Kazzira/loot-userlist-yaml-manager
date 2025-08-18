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
#include <map>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/rule/s_loot_group_rule_entry.hpp"
#include "luyamlman/types/t_loot_group_name.hpp"
#include "luyamlman/types/t_plugin_name.hpp"

namespace luyamlman::manager {

struct s_config
{
        std::vector<luyamlman::rule::s_loot_group_rule_entry>
            m_loot_group_rules;
        std::map<
            luyamlman::types::t_loot_group_name,
            std::vector<luyamlman::types::t_plugin_name>>
            m_plugin_starting_points;
};
} // namespace luyamlman::manager
