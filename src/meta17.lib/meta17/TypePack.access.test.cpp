#include "TypePack.access.h"

#include "Type.ops.h"

using namespace meta17;

static_assert(same<TypeAt<1, TypePack<int, char, float>>, char>);
static_assert(type_at<1, TypePack<int, char, float>> == type<char>);

static_assert(same<TypeLast<TypePack<int, char>>, char>);
static_assert(type_last<TypePack<int, char>> == type<char>);
