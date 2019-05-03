#include <meta17/TemplateOfTypes.indexOf.h>

#include <meta17/TypePack.h>

using namespace meta17;

static_assert(template_contains<int, TypePack<int, char>>);

static_assert(templateCountOf<int>(type<TypePack<int, char, int>>) == 2);
static_assert(template_count_of<int, TypePack<int, char, int>> == 2);

static_assert(template_index_of<int, TypePack<char, int, unsigned>> == 1);
static_assert(template_index_of<int, TypePack<float, double>> == 2);

// static_assert(checkedIndexOf<int>(type_pack<void, char, int>) == 2);
// static_assert(checked_index_of<int, TypePack<void, char, int>> == 2);
