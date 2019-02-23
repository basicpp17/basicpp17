#include "meta17/IndexPack.extract.h"

#include "meta17/IndexPack.ops.h" // index_pack == index_pack

using namespace meta17;

static_assert(extract_index_pack<IndexPack<1, 2, 3>> == index_pack<1, 2, 3>);

template<class T, T...>
struct Dummy {};
static_assert(extract_index_pack<Dummy<size_t, 1, 2>> == index_pack<1, 2>);
