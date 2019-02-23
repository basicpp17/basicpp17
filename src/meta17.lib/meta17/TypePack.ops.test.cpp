#include "TypePack.ops.h"

using namespace meta17;

static_assert(type_pack<int, float> == type_pack<int, float>);
static_assert(type_pack<int, float> != type_pack<int, float, double>);
static_assert(type_pack<int, float> != TypePack<int, double>{});

static_assert(type_pack<char> + type_pack<int> + type<float> == type_pack<char, int, float>);
static_assert(type<char> + type_pack<int, float> == type_pack<char, int, float>);
