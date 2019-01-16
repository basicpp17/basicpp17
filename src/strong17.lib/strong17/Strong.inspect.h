#pragma once

#include "Strong.h"

#include "meta17/Type.h"
#include "meta17/TypePack.indexOf.h"

#include "meta17/TemplateOfTypes.h"

namespace strong17 {

/// tag inspection
template<class CandidateTag, class Value, class... Tags>
constexpr auto hasTag(meta17::Type<Strong<Value, Tags...>>, meta17::Type<CandidateTag> = {}) {
    return (std::is_same_v<CandidateTag, Tags> || ...);
}

/// tag inspection
template<class CandidateTag, class Value, class... Tags>
constexpr auto contains(meta17::Type<Strong<Value, Tags...>>, meta17::Type<CandidateTag> = {}) {
    return (std::is_same_v<CandidateTag, Tags> || ...);
}

} // namespace strong17
