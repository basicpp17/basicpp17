#include <meta17/TemplateOfTypes.transform.h>

#include <meta17/Type.ops.h>
#include <meta17/TypePack.h>

using namespace meta17;

template<class... Ts>
struct MyWrap {};

// transform TypePack -> MyWrap
static_assert(transformTemplate<MyWrap>(type<TypePack<int, char>>) == type<MyWrap<int, char>>);
static_assert(type<TransformTemplate<MyWrap, TypePack<int, char>>> == type<MyWrap<int, char>>);
