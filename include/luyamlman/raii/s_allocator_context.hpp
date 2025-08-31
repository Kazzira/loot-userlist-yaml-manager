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

#include <memory>
#include <type_traits>

namespace luyamlman::raii {

template <class T, template <class> class AAllocatorType = std::allocator>
class s_allocator_context
{

    public:
        ~s_allocator_context() noexcept
        {
            if constexpr( std::is_same_v<AAllocatorType<T>, std::allocator<T>> )
            {
                return;
            }
            else
            {
                AAllocatorType<T>::reset_used();
            }
        }
};

} // namespace luyamlman::raii
