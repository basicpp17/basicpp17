#include "TypePack.h"

using namespace meta17;

using FloatPack = TypePack<float, double>;
constexpr auto floatPack() { return type_pack<float, double>; }
