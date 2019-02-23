#include "meta17/IndexTypePack.h"

using namespace meta17;

using IntFloat = TypePack<IndexType<0, int>, IndexType<1, float>>;
constexpr auto intFloat() { return type_pack<IndexType<0, int>, IndexType<1, float>>; }
