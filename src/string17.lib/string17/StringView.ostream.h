#pragma once
#include "StringView.h"

#include <ostream>

namespace string17 {

auto operator<<(std::ostream& out, StringView v) -> std::ostream& {
    return out.write(v.begin, v.size()); //
}

} // namespace string17
