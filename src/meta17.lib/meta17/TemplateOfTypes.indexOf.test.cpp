#include "TemplateOfTypes.indexOf.h"

#include "TypePack.h"

using namespace meta17;

static_assert(template_contains_of<int, TypePack<int, char>>);

static_assert(template_count_of<int, TypePack<int, char, int>> == 2);

static_assert(type_template_overflow_index_of<int, TypePack<char, int, unsigned>> == 1);
static_assert(type_template_overflow_index_of<int, TypePack<float, double>> == 2);

static_assert(type_template_index_of<int, TypePack<void, char, int>> == 2);
// static_assert(type_template_index_of<double, TypePack<void, char, int>> == 0);
