#include <meta17/TemplateOfTypes.h>

#include <meta17/TemplateOfTypes.transform.h>

#include <meta17/Type.ops.h>
#include <meta17/TypePack.h>

#include <type_traits>

using namespace meta17;

template<class... Ts>
struct MyWrap {};

static_assert(type<TransformTemplate<MyWrap, TypePack<int, char>>> == type<MyWrap<int, char>>);
