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
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/s_error.hpp"

luyamlman::error::s_error::s_error(
    luyamlman::error::v_error_details a_details
) noexcept
    : m_details( std::move( a_details ) )
{
}

luyamlman::error::s_error::iterator
luyamlman::error::s_error::begin() noexcept
{
    return m_additional_errors.begin();
}

luyamlman::error::s_error::const_iterator
luyamlman::error::s_error::begin() const noexcept
{
    return m_additional_errors.begin();
}

luyamlman::error::s_error::iterator
luyamlman::error::s_error::end() noexcept
{
    return m_additional_errors.end();
}

luyamlman::error::s_error::const_iterator
luyamlman::error::s_error::end() const noexcept
{
    return m_additional_errors.end();
}

luyamlman::error::s_error::reverse_iterator
luyamlman::error::s_error::rbegin() noexcept
{
    return m_additional_errors.rbegin();
}

luyamlman::error::s_error::const_reverse_iterator
luyamlman::error::s_error::rbegin() const noexcept
{
    return m_additional_errors.rbegin();
}

luyamlman::error::s_error::reverse_iterator
luyamlman::error::s_error::rend() noexcept
{
    return m_additional_errors.rend();
}

luyamlman::error::s_error::const_reverse_iterator
luyamlman::error::s_error::rend() const noexcept
{
    return m_additional_errors.rend();
}

bool
luyamlman::error::s_error::empty() const noexcept
{
    return m_additional_errors.empty();
}

size_t
luyamlman::error::s_error::size() const noexcept
{
    return m_additional_errors.size() + 1;
}

const luyamlman::error::v_error_details&
luyamlman::error::s_error::details() const noexcept
{
    return m_details;
}

void
luyamlman::error::s_error::return_value(
    std::any a_return_value
) noexcept
{
    m_return_value = std::move( a_return_value );
}

template <typename T>
std::optional<T>
luyamlman::error::s_error::return_value_as() noexcept
{
    if( !m_return_value.has_value() )
    {
        return std::nullopt;
    }

    if( T* p_value = std::any_cast<T>( &( *m_return_value ) ) )
    {
        T value = std::move( *p_value );
        m_return_value.reset();
        return std::make_optional( std::move( value ) );
    }

    return std::nullopt;
}

void
luyamlman::error::s_error::insert_additional_error(
    s_error a_error
)
{
    m_additional_errors.push_back( std::move( a_error ) );
}
