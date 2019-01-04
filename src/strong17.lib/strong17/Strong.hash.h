#pragma once
#include "Strong.h"

namespace std {

template<class T, class... Tags>
struct hash<strong17::Strong<T, Tags...>> {
    std::size_t operator()(strong17::Strong<T, Tags...> a) const { return hash<T>{}(a.v); }
};

} // namespace std
