#include "TypePack.access.h"

using namespace meta17;

static_assert(TypeAt<Index<1>, TypePack<int, char, float>>{} == type<char>);
static_assert(type_at<Index<1>, TypePack<int, char, float>> == type<char>);

static_assert(TypeLast<TypePack<int, char>>{} == type<char>);
static_assert(type_last<TypePack<int, char>> == type<char>);
