#pragma once
#include "StringStore.h"

#include <ostream>

namespace string17 {

template<size_t N>
auto operator<<(std::ostream& out, const StringStore<N>& o) -> std::ostream& {
    return out.write(o.data, N);
}

} // namespace string17
