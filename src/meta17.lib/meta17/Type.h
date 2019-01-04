#pragma once

namespace meta17 {

/// transport any type
template<class T>
struct Type {};

template<class T>
constexpr auto type = Type<T>{};

} // namespace meta17
