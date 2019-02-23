#include "meta17/Const.h"

using namespace meta17;

using Answer = Const<42>;

constexpr auto answer() -> Answer { return _const<42>; }
