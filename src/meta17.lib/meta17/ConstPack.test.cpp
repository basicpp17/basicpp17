#include "meta17/ConstPack.h"

using namespace meta17;

using FibSeq = ConstPack<1, 1, 2, 3, 5, 8, 13, 21>;

constexpr auto linearSeq() { return const_pack<1, 2, 3, 4, 5, 6>; }
