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
#include <list>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/v_error_details.hpp"

namespace luyamlman::error {

class s_error
{
    public:
        using iterator         = std::list<s_error>::iterator;
        using const_iterator   = std::list<s_error>::const_iterator;
        using reverse_iterator = std::list<s_error>::reverse_iterator;
        using const_reverse_iterator
            = std::list<s_error>::const_reverse_iterator;

    public:
        s_error(
            luyamlman::error::v_error_details a_details
        )
            : m_details( std::move( a_details ) )
        {
        }

    public:
        iterator
        begin()
        {
            return m_additional_errors.begin();
        }

        const_iterator
        begin() const
        {
            return m_additional_errors.begin();
        }

        iterator
        end()
        {
            return m_additional_errors.end();
        }

        const_iterator
        end() const
        {
            return m_additional_errors.end();
        }

        reverse_iterator
        rbegin()
        {
            return m_additional_errors.rbegin();
        }

        const_reverse_iterator
        rbegin() const
        {
            return m_additional_errors.rbegin();
        }

        reverse_iterator
        rend()
        {
            return m_additional_errors.rend();
        }

        const_reverse_iterator
        rend() const
        {
            return m_additional_errors.rend();
        }

        bool
        empty() const
        {
            return m_additional_errors.empty();
        }

        size_t
        size() const
        {
            return m_additional_errors.size() + 1;
        }

    public:
        const luyamlman::error::v_error_details&
        details() const
        {
            return m_details;
        }

    public:
        void
        consolidate_errors();

        void
        insert_additional_error(
            s_error& a_error
        )
        {
            m_additional_errors.push_back( std::move( a_error ) );
        }

    private:
        luyamlman::error::v_error_details m_details;
        std::list<s_error>                m_additional_errors;
};
} // namespace luyamlman::error
