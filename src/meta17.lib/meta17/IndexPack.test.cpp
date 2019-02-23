#include "meta17/IndexPack.h"

using namespace meta17;

using MyPack = IndexPack<1, 2, 3>;
constexpr auto myPack() { return index_pack<1, 2, 3>; }
