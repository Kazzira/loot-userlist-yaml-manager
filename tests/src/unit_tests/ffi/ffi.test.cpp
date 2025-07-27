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
/////////////////////////////////////////////////////////////////////////////
// THIRD PARTY INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include <catch2/catch_all.hpp>

/////////////////////////////////////////////////////////////////////////////
// TESTS INCLUDES
/////////////////////////////////////////////////////////////////////////////
#include "luyamlman_tests/ffi/ffi_wrapper.hpp"

TEST_CASE(
    "ffi: Test construction of wrapper non-existant files",
    "[ffi][ffi_construction]"
)
{
    luyamlman_tests::ffi::s_ffi_wrapper wrapper("no_load_order.txt", "no_config.json");
    REQUIRE(!wrapper);
    REQUIRE(wrapper.construction_return_code() == LUYAMLMAN_OK());
}