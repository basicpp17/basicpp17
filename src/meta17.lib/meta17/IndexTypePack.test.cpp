#include "meta17/IndexTypePack.extract.h"
#include "meta17/IndexTypePack.h"
#include "meta17/IndexTypePack.make.h"
#include "meta17/IndexTypePack.trait.h"

#include "meta17/IndexPack.ops.h"
#include "meta17/TypePack.ops.h"

using namespace meta17;

static_assert(is_index_type_pack<TypePack<>>);
static_assert(is_index_type_pack<TypePack<IndexType<23, int>>>);
static_assert(!is_index_type_pack<int>);
static_assert(!is_index_type_pack<TypePack<int>>);
static_assert(!is_index_type_pack<TypePack<IndexType<23, int>, int>>);

static_assert(extract_index_pack<TypePack<IndexType<23, int>>> == index_pack<23>);
static_assert(extract_type_pack<TypePack<IndexType<23, int>>> == type_pack<int>);

static_assert(make_index_type_pack<TypePack<>> == type_pack<>);
static_assert(makeIndexTypePack<char, int>() == type_pack<IndexType<0, char>, IndexType<1, int>>);
static_assert(makeIndexTypePack<IndexType<23, char>, int>() == type_pack<IndexType<23, char>, IndexType<24, int>>);
