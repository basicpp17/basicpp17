#pragma once

namespace meta17 {

struct None { // TODO Move to proper file
    bool operator==(const None&) const { return true; }
    bool operator!=(const None&) const { return false; }
};

} // namespace meta17
