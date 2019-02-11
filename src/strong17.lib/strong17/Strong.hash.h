#pragma once
#include "Strong.h"

#include "Strong.base.h"

#include <functional>

namespace strong17 {

template<class T, class... Tags>
auto getHasher(Strong<T, Tags...>) -> std::hash<T>;

template<class T>
using Hasher = decltype(getHasher(Base<T>{}));

} // namespace strong17

namespace std {

template<class T, class... Tags>
struct hash<strong17::Strong<T, Tags...>> : std::hash<T> {};

} // namespace std
