#pragma once
#include "Strong.h"

#include <ostream>

namespace strong17 {

template<class Chr, class Traits, class T, class... Tags>
auto operator<<(std::basic_ostream<Chr, Traits>& out, const Strong<T, Tags...>& s) -> decltype(out)& {
    return out << s.v;
}

} // namespace strong17
