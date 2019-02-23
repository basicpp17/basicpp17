#include "meta17/IndexType.h"

using namespace meta17;

using FloatIndex = IndexType<1, float>;
constexpr auto floatIndex() { return index_type<1, float>; }
