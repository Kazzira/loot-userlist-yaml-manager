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
#include <variant>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/details_types/allocation_failure.hpp"

namespace luyamlman::error {

/**
 * @brief Variant type for error details in the LOOT Userlist.yaml Manager.
 *
 * This variant can hold different types of error details, allowing for flexible
 * error handling.
 */
using v_error_details
    = std::variant<luyamlman::error_details_types::s_allocation_failure>;

} // namespace luyamlman::error
