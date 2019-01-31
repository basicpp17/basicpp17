#pragma once

#include "None.h"

#include <ostream>

namespace meta17 {

template<class Chr, class Traits>
auto operator<<(std::basic_ostream<Chr, Traits>& out, const None&) -> decltype(out)& {
    out << "";
    return out;
}

} // namespace meta17
