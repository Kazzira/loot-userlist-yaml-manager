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
template <template <class> class AAllocator = std::allocator>
class s_error
{
    public:
        using iterator         = std::list<s_error>::iterator;
        using const_iterator   = std::list<s_error>::const_iterator;
        using reverse_iterator = std::list<s_error>::reverse_iterator;
        using const_reverse_iterator
            = std::list<s_error>::const_reverse_iterator;

    public:
        explicit inline s_error( luyamlman::error::v_error_details a_details
        ) noexcept;

    public:
        inline iterator
        begin() noexcept;

        inline const_iterator
        begin() const noexcept;

        inline iterator
        end() noexcept;

        inline const_iterator
        end() const noexcept;

        inline reverse_iterator
        rbegin() noexcept;

        inline const_reverse_iterator
        rbegin() const noexcept;

        inline reverse_iterator
        rend() noexcept;

        inline const_reverse_iterator
        rend() const noexcept;

        inline bool
        empty() const noexcept;

        inline size_t
        size() const noexcept;

    public:
    public:
        inline const luyamlman::error::v_error_details&
        details() const noexcept;

        inline void
        return_value( std::any a_return_value ) noexcept;

        template <typename T>
        inline std::optional<T>
        return_value_as() noexcept;

    public:
        inline void
        consolidate_errors() noexcept;

        inline void
        insert_additional_error( s_error a_error );

    private:
        luyamlman::error::v_error_details       m_details;
        std::list<s_error, AAllocator<s_error>> m_additional_errors;
        std::optional<std::any>                 m_return_value;
};
} // namespace luyamlman::error

namespace luyamlman {

template <typename T, template <class> typename AAllocator = std::allocator>
using result = std::expected<T, luyamlman::error::s_error<AAllocator>>;

template <typename T>
using result_jsondumped = std::expected<T, std::string>;

template <typename T>
using result_jsondumped_cstr = std::expected<T, char*>;

} // namespace luyamlman

// Inline include.
#include "luyamlman/error/s_error.inl"
