#pragma once

#include "Strong.h"

#include "meta17/Type.h"
#include "meta17/TypePack.indexOf.h"

#include "meta17/TemplateOfTypes.h"

namespace strong17 {

using meta17::Type;

/// tag inspection
template<class CandidateTag, class Value, class... Tags>
constexpr auto hasTag(Type<Strong<Value, Tags...>>, Type<CandidateTag> = {}) {
    return (std::is_same_v<CandidateTag, Tags> || ...);
}

/// type inspection
template<class CandidateType, class Value, class... Tags>
constexpr auto hasType(Type<Strong<Value, Tags...>>, Type<CandidateType> = {}) {
    return std::is_same_v<Value, CandidateType>;
}

} // namespace strong17
