#include "Variant.trait.h"

#include <gtest/gtest.h>
#include <utility>

using namespace variant17;

TEST(Variant, trait) {
    using T = Variant<int, double, char, short, bool>;
    static_assert(is_variant<T>);

    struct S {
        int i;
    };
    static_assert(!is_variant<S>);

    using P = std::pair<int, double>;
    static_assert(!is_variant<P>);

    static_assert(!is_variant<int>);
}
