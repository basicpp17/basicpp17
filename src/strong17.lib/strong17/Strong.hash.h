#pragma once
#include "Strong.h"

#include "Strong.base.h"

#include <functional>

namespace strong17 {

template<class T, class... Tags>
auto getHasher(Strong<T, Tags...>) -> std::hash<Strong<T, Tags...>>;

template<class T>
using Hasher = decltype(getHasher(Base<T>{}));

} // namespace strong17

namespace std {

template<class T, class... Tags>
struct hash<strong17::Strong<T, Tags...>> {
    size_t operator()(strong17::Strong<T, Tags...> a) const { return std::hash<T>{}(a.v); }
};

} // namespace std
