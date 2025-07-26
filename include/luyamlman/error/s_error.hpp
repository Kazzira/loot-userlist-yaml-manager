#pragma once
/*
Copyright (C) 2024-2025 Zachary Dakota Meyer. All rights reserved.

This file is part of the LOOT Userlist.yaml Manager project.

LOOT Userlist.yaml Manager is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

LOOT Userlist.yaml Manager is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with LOOT Userlist.yaml Manager.  If not, see <http://www.gnu.org/licenses/>.
*/

//PAGE: Includes ------------------------------------------------------------/
//////////////////////////////////////////////////////////////////////////////
// STANDARD LIBRARY INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include <vector>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/error_details_types.hpp"


namespace luyamlman::error {


class s_error
{
public:
    s_error(
        luyamlman::error::v_error_details a_details
    ) : m_details(std::move(a_details))
    {
    }
public:
    luyamlman::error::v_error_details&
    details() { return m_details; }

    const luyamlman::error::v_error_details&
    details() const { return m_details; }
public:
    void
    consolidate_errors();

    void
    insert_additional_error(
        s_error& a_error
    ) { m_additional_errors.push_back(std::move(a_error)); }
private:
    luyamlman::error::v_error_details m_details;
    std::vector<s_error>              m_additional_errors;
};


}