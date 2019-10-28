#include "TemplateOfValues.h"

using namespace meta17;

template<int...>
struct MyValues {};

using MyTemplate = TemplateOfValues<MyValues>;
