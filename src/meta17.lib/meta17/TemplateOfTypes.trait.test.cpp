#include <meta17/TemplateOfTypes.trait.h>

using namespace meta17;

template<class...>
struct Dummy {};

static_assert(is_type_template<Dummy<>, Dummy>);
static_assert(is_type_template<Dummy<int, float, double>, Dummy>);
static_assert(!is_type_template<int, Dummy>);
