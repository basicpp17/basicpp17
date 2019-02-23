#include <meta17/TemplateOfTypes.extract.h>

#include <meta17/TypePack.ops.h> // type_pack == type_pack

using namespace meta17;

template<class...>
struct Dummy {};

static_assert(count_types<Dummy<>> == 0);
static_assert(count_types<Dummy<int, double, float>> == 3);

static_assert(extract_type_pack<Dummy<>> == type_pack<>);
static_assert(extract_type_pack<Dummy<int, double, float>> == type_pack<int, double, float>);

static_assert(extract_head_type<Dummy<int>> == type<int>);

static_assert(extract_tail_type_pack<Dummy<int>> == type_pack<>);
static_assert(extract_tail_type_pack<Dummy<int, double, float>> == type_pack<double, float>);
