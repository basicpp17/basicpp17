#include "TemplateOfTypes.iterate.h"

#include "Type.wrap.h" // UnwrapType
#include <cinttypes>

using namespace meta17;

template<class...>
struct Dummy {};

static_assert(forEachTemplateType(type<Dummy<int32_t, float>>, [s = 0](auto t) mutable {
                  using T = UnwrapType<decltype(t)>;
                  s += sizeof(T);
                  return s;
              }) == 8);
