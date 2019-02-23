#include <meta17/TemplateOfValues.extract.h>

#include <meta17/Const.ops.h> // _const == _const
#include <meta17/ConstPack.ops.h> // const_pack == const_pack

using namespace meta17;

template<int...>
struct MyValues {};

static_assert(count_values<MyValues<1, 2, 3>> == 3);

static_assert(extract_const_pack<MyValues<1, 2, 3>> == const_pack<1, 2, 3>);

static_assert(extract_head_const<MyValues<1, 2, 3>> == _const<1>);

static_assert(extract_tail_const_pack<MyValues<1, 2, 3>> == const_pack<2, 3>);
