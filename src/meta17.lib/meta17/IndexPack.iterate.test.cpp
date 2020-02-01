#include "IndexPack.iterate.h"

#include "Index.wrap.h" // UnwrapType
#include <cinttypes>

using namespace meta17;

static_assert(forEachIndex(index_pack<12, 23>, [s = 0](auto i) mutable {
                  s += to_value<decltype(i)>;
                  return s;
              }) == 35);
