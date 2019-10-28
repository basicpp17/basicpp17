#include "meta17/TemplateOfTypes.wrap.h"

#include "meta17/same.h"

using namespace meta17;

template<class...>
struct Dummy {};

static_assert(same<UnwrapTemplate<Dummy<int>, TemplateOfTypes<Dummy>>, int>);

static_assert(same<ToTemplate<TemplateOfTypes<Dummy>, int, float>, Dummy<int, float>>);
