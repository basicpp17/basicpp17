#include "meta17/TypeList.h"
#include "meta17/TypeList.make.h"
#include "meta17/TypeList.ops.h"

#include "meta17/Type.ops.h"

using namespace meta17;

static_assert(MakeTypeList<TypePack<>>::count == 0);
static_assert(MakeTypeList<TypePack<int, float>>::count == 2);

static_assert(MakeTypeList<TypePack<int, float>>::contains<int>());
static_assert(!MakeTypeList<TypePack<int, float>>::contains<double>());

static_assert(2 == MakeTypeList<TypePack<char, int, float>>::indexOf<float>());

static_assert(1 == MakeTypeList<TypePack<char, int, float>>::countIndex<1>());
static_assert(0 == MakeTypeList<TypePack<char, int, float>>::countIndex<9>());

static_assert(type<char> == MakeTypeList<TypePack<char, int>>::at<0>());
static_assert(type<int> == MakeTypeList<TypePack<char, int>>::At<1>{});
static_assert(type<char> == MakeTypeList<TypePack<char, int>>{}[Index<0>{}]);

static_assert(2 == MakeTypeList<TypePack<char, int, char>>::countIfType([](auto f) { return f == type<char>; }));

// static_assert(
//    ToTypeList<IndexType<0, char>, IndexType<2, int>>{} //
//    == ToTypeList<char, float, int>::filterIfType( //
//           [](auto f) { return f != type<float>; }));
