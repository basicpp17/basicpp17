#include "TypePack.access.h"
#include "TypePack.recurse.h"
#include "TypePack.h"
#include "TypePack.indexOf.h"
#include "TypePack.ops.h"
#include "TypePack.trait.h"
#include "TypePack.wrap.h"

#include "Type.ops.h" // type == type

using namespace meta17;

static_assert(is_type_pack<TypePack<int>>);
static_assert(is_type_pack<TypePack<>>);
static_assert(!is_type_pack<int>);

static_assert(TypePack<int, float>{} == TypePack<int, float>{});
static_assert(TypePack<int, float>{} != TypePack<int, float, double>{});
static_assert(TypePack<int, float>{} != TypePack<int, double>{});

static_assert(to_type_pack<int, Type<float>> == TypePack<int, float>{});
static_assert(to_type_pack<TypePack<int, float>> == type_pack<int, float>);

static_assert(typeCount<char, int, float>() == 3);
static_assert(type_head<TypePack<char, int, float>> == Type<char>{});
static_assert(type_tail<TypePack<char, int, float>> == type_pack<int, float>);

static_assert(type_pack<char> + type_pack<int> + type<float> == type_pack<char, int, float>);
static_assert(type<char> + type_pack<int, float> == type_pack<char, int, float>);

static_assert(TypeAt<Index<1>, TypePack<int, char, float>>{} == type<char>);
static_assert(TypeLast<TypePack<int, char>>{} == type<char>);

static_assert(countOf<int>(type_pack<int, char, int>) == 2);
static_assert(checkedIndexOf<int>(type_pack<void, char, int>) == 2);
