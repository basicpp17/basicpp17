#include "TemplateOfValues.trait.h"

using namespace meta17;

template<int...>
struct MyValues {};

static_assert(is_value_template<MyValues<>, MyValues>);
static_assert(is_value_template<MyValues<1, 2, 3>, MyValues>);
static_assert(!is_value_template<int, MyValues>);
