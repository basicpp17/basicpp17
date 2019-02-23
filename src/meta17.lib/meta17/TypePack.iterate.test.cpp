#include "TypePack.iterate.h"

#include "Type.wrap.h" // UnwrapType
#include <cinttypes>

using namespace meta17;

static_assert(forEachType(type_pack<int32_t, float>, [s = 0](auto t) mutable {
                  using T = UnwrapType<decltype(t)>;
                  s += sizeof(T);
                  return s;
              }) == 8);

static_assert(allTypesOf(type_pack<int32_t, float>, [](auto t) {
    using T = UnwrapType<decltype(t)>;
    return sizeof(T) == 4;
}));
