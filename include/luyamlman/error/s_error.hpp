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
#include <any>
#include <cstddef>
#include <expected>
#include <list>
#include <optional>

//////////////////////////////////////////////////////////////////////////////
// PROJECT INCLUDES
//////////////////////////////////////////////////////////////////////////////
#include "luyamlman/error/v_error_details.hpp"

namespace luyamlman::error {

/**
 * @brief Represents an error within the library.
 *
 * This class is used to encapsulate an error that has occurred, along with
 * any additional errors that may have occurred during the same operation.
 *
 * This class is the error type used in `luyamlman::result<T>`, which itself
 * is an alias for `std::expected<T, luyamlman::error::s_error>`
 */
class s_error
{
    public:
        using iterator         = std::list<s_error>::iterator;
        using const_iterator   = std::list<s_error>::const_iterator;
        using reverse_iterator = std::list<s_error>::reverse_iterator;
        using const_reverse_iterator
            = std::list<s_error>::const_reverse_iterator;

    public:
        explicit s_error(
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

        void
        return_value(
            std::any a_return_value
        )
        {
            m_return_value = std::move( a_return_value );
        }

        template <typename T>
        std::optional<T>
        return_value_as()
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

    public:
        void
        consolidate_errors();

        void
        insert_additional_error(
            s_error a_error
        )
        {
            m_additional_errors.push_back( std::move( a_error ) );
        }

    private:
        luyamlman::error::v_error_details m_details;
        std::list<s_error>                m_additional_errors;
        std::optional<std::any>           m_return_value;
};
} // namespace luyamlman::error

namespace luyamlman {

template <typename T>
using result = std::expected<T, luyamlman::error::s_error>;

template <typename T>
using result_jsondumped = std::expected<T, std::string>;

template <typename T>
using result_jsondumped_cstr = std::expected<T, char*>;

} // namespace luyamlman
