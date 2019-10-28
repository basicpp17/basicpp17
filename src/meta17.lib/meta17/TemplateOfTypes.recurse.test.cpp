#include "TemplateOfTypes.recurse.h"

#include "Type.ops.h"
#include "TypePack.ops.h" // type_pack == type_pack

using namespace meta17;

template<class...>
struct Dummy {};

static_assert(count_template_types<Dummy<>> == 0);
static_assert(count_template_types<Dummy<int, double, float>> == 3);

static_assert(template_type_head<Dummy<int>> == type<int>);

static_assert(same<TemplateTypeTail<Dummy<int>>, Dummy<>>);
static_assert(same<TemplateTypeTail<Dummy<int, double, float>>, Dummy<double, float>>);
