#include "Value.ref.h"

using namespace meta17;

struct Point {
    int x{};
    int y{};
};

// note: msvc requires the constant to be outside of a function or the content is not accessable
constexpr auto referencePoint = Point{23, 42};

constexpr auto makeValue() { return value_ref<referencePoint>; }

using ReferencePoint = decltype(makeValue());
static_assert(ReferencePoint::v.x == 23);
static_assert(ReferencePoint::v.y == 42);
