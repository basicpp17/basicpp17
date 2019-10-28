#include "TypePack.indexOf.h"

using namespace meta17;

static_assert(countOf<int>(type_pack<int, char, int>) == 2);
static_assert(count_of<int, TypePack<int, char, int>> == 2);

static_assert(!contains_of<int, TypePack<float, double>>);
static_assert(contains_of<int, TypePack<char, int, unsigned>>);

static_assert(type_pack_overflow_index_of<int, TypePack<char, int, unsigned>> == 1);
static_assert(type_pack_overflow_index_of<int, TypePack<float, double>> == 2);

static_assert(typePackIndexOf<int>(type_pack<void, char, int>) == 2);
static_assert(type_pack_index_of<int, TypePack<void, char, int>> == 2);
