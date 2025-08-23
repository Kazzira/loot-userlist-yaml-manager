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
#include <mutex>
#include <optional>

namespace luyamlman::memory {

template <typename T>
class singleton
{
    public:
        template <typename... AArgs>
        static T&
        get_instance(
            AArgs&&... a_args
        )
        {
            if( !m_instance.has_value() )
            {
                std::lock_guard<std::mutex> lock( m_mutex );

                if( !m_instance.has_value() )
                {
                    m_instance.emplace( std::forward<AArgs&&>( a_args )... );
                }
            }

            return *m_instance;
        }

        static void
        reset_instance() noexcept
        {
            m_instance.reset();
        }

    private:
        inline static std::optional<T> m_instance;
        inline static std::mutex       m_mutex;
};
} // namespace luyamlman::memory
