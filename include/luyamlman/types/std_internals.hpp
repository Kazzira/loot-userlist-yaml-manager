#pragma once

////////////////////////////////////////////////////////////////////////////////
// STANDARD LIBRARY INCLUDES
////////////////////////////////////////////////////////////////////////////////
#include <list>
#include <map>
#include <set>

namespace luyamlman::types {

#ifdef _WIN32
template <typename T>
using t_std_set_tree_node = std::_Tree_node<T, void* __ptr64>;
#else
template <typename T>
using t_std_set_tree_node = std::_Rb_tree_node<T>;
#endif

} // namespace luyamlman::types
