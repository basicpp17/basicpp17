#pragma once

namespace meta17 {

// faster than std::same_v (less type instantiations)
template<class A, class B>
constexpr auto same = false;

template<class A>
constexpr auto same<A, A> = true;

} // namespace meta17
