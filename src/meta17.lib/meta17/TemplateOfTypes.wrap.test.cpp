#include <meta17/TemplateOfTypes.wrap.h>

using namespace meta17;

template<class...>
struct Dummy {};

static_assert(std::is_same_v<UnwrapTemplate<Dummy<int>, TemplateOfTypes<Dummy>>, int>);

static_assert(std::is_same_v<ToTemplate<TemplateOfTypes<Dummy>, int, float>, Dummy<int, float>>);
