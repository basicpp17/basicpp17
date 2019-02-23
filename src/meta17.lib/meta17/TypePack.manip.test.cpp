#include "TypePack.manip.h"

using namespace meta17;

static_assert(removeType(type_pack<int, float, int>, type<int>) == type_pack<float>);
static_assert(removeType(type_pack<char, int, long>, type<float>) == type_pack<char, int, long>);
static_assert(RemoveType<int, TypePack<char, int, long>>{} == type_pack<char, long>);

static_assert(removeTypes(type_pack<char, int, long>, type_pack<char, int>) == type_pack<long>);
static_assert(RemoveTypes<TypePack<char, int>, TypePack<char, int, long>>{} == type_pack<long>);

static_assert(replaceType(type_pack<int, double>, type<int>, type<float>) == type_pack<float, double>);
static_assert(ReplaceType<int, float, TypePack<int, double>>{} == type_pack<float, double>);
