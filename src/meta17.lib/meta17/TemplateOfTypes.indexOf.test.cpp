#include <meta17/TemplateOfTypes.indexOf.h>

#include <meta17/TypePack.h>

using namespace meta17;

static_assert(template_contains<int, TypePack<int, char>>);
