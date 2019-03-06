#include "Strong.ops.h"

#include "Strong.opaque.h"
#include "Strong.ostream.h"

#include <gtest/gtest.h>
#include <sstream>

using namespace strong17;

struct Custom {
    std::string value;
};

template<class Chr, class Traits>
auto operator<<(std::basic_ostream<Chr, Traits>& out, const Custom& d) -> decltype(out)& {
    return out << d.value;
}

using PositionExplicit = Strong<int, struct PositionTag>;
using VelocityExplicit = Strong<float, struct VelocityTag>;
using ActiveExplicit = Strong<bool, struct ActiveTag>;
using CustomExplicit = Strong<Custom, struct CustomTag>;

STRONG_OPAQUE(PositionOpaque, int, struct PositionTag);
STRONG_OPAQUE(VelocityOpaque, float, struct VelocityTag);
STRONG_OPAQUE(ActiveOpaque, bool, struct ActiveTag);
STRONG_OPAQUE(CustomOpaque, Custom, struct CustomTag);

TEST(Strong, ostream) {
    auto p = PositionExplicit{1};
    auto v = VelocityExplicit{2.3};
    auto a = ActiveExplicit{false};
    auto d = CustomExplicit{{"Custom"}};
    std::stringstream actual, expected;
    actual << p << " " << v << " " << a << " " << d;
    expected << "1 2.3 0 Custom";
    EXPECT_EQ(actual.str(), expected.str());
}

TEST(StrongOpaque, ostream) {
    auto p = PositionOpaque{1};
    auto v = VelocityOpaque{2.3};
    auto a = ActiveOpaque{false};
    auto d = CustomOpaque({"Custom"});
    std::stringstream actual, expected;
    actual << p << " " << v << " " << a << " " << d;
    expected << "1 2.3 0 Custom";
    EXPECT_EQ(actual.str(), expected.str());
}
