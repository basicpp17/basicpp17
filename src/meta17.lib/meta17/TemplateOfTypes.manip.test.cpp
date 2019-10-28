#include "meta17/TemplateOfTypes.manip.h"

#include "meta17/Type.ops.h" // type == type
#include "meta17/same.h"

using namespace meta17;

template<class...>
struct Dummy {};

static_assert(same<AddTypeToTemplate<float, Dummy<int>>, Dummy<int, float>>);
static_assert(addTypeToTemplate<float>(type<Dummy<int>>) == type<Dummy<int, float>>);

static_assert(same<AddTypesToTemplate<TypePack<float, double>, Dummy<int>>, Dummy<int, float, double>>);
static_assert(addTypesToTemplate<float, double>(type<Dummy<int>>) == type<Dummy<int, float, double>>);
