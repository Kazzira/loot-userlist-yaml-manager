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

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::s_error(
    luyamlman::error::v_error_details a_details
) noexcept
    : m_details( std::move( a_details ) )
{
}

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::iterator
luyamlman::error::s_error<AAllocator>::begin() noexcept
{
    return m_additional_errors.begin();
}

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::const_iterator
luyamlman::error::s_error<AAllocator>::begin() const noexcept
{
    return m_additional_errors.begin();
}

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::iterator
luyamlman::error::s_error<AAllocator>::end() noexcept
{
    return m_additional_errors.end();
}

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::const_iterator
luyamlman::error::s_error<AAllocator>::end() const noexcept
{
    return m_additional_errors.end();
}

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::reverse_iterator
luyamlman::error::s_error<AAllocator>::rbegin() noexcept
{
    return m_additional_errors.rbegin();
}

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::const_reverse_iterator
luyamlman::error::s_error<AAllocator>::rbegin() const noexcept
{
    return m_additional_errors.rbegin();
}

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::reverse_iterator
luyamlman::error::s_error<AAllocator>::rend() noexcept
{
    return m_additional_errors.rend();
}

template <template <class> typename AAllocator>
luyamlman::error::s_error<AAllocator>::const_reverse_iterator
luyamlman::error::s_error<AAllocator>::rend() const noexcept
{
    return m_additional_errors.rend();
}

template <template <class> typename AAllocator>
bool
luyamlman::error::s_error<AAllocator>::empty() const noexcept
{
    return m_additional_errors.empty();
}

template <template <class> typename AAllocator>
size_t
luyamlman::error::s_error<AAllocator>::size() const noexcept
{
    return m_additional_errors.size() + 1;
}

template <template <class> typename AAllocator>
const luyamlman::error::v_error_details&
luyamlman::error::s_error<AAllocator>::details() const noexcept
{
    return m_details;
}

template <template <class> typename AAllocator>
void
luyamlman::error::s_error<AAllocator>::return_value(
    std::any a_return_value
) noexcept
{
    m_return_value = std::move( a_return_value );
}

template <template <class> typename AAllocator>
template <typename T>
std::optional<T>
luyamlman::error::s_error<AAllocator>::return_value_as() noexcept
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

template <template <class> typename AAllocator>
void
luyamlman::error::s_error<AAllocator>::insert_additional_error(
    s_error a_error
)
{
    m_additional_errors.push_back( std::move( a_error ) );
}

template <template <class> typename AAllocator>
void
luyamlman::error::s_error<AAllocator>::consolidate_errors() noexcept
{
    for( auto& error : m_additional_errors )
    {
        if( error.m_additional_errors.empty() )
        {
            continue;
        }

        error.consolidate_errors();

        //
        // Will need to test to make sure that iterators work correctly here.
        //
        m_additional_errors
            .splice( m_additional_errors.end(), error.m_additional_errors );
    }
}
